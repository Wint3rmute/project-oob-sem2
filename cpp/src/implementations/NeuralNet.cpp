//
// Created by wint3rmute on 3/16/18.
//

#include "../headers/NeuralNet.h"

#include <iostream>
using namespace std;


double sigmoid(double value)
{
    return 1.0 / ( 1.0 + exp(-value) );
}


/**
 * A little helper - this value is used as a timestamp for saving into the network archive
 */
string getCurrentTime() {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d_%m___%I_%M_%S",timeinfo);
    std::string str(buffer);

    return str;
}

NeuralNet::NeuralNet(NetworkParams * params) : generator(0.0, 1.0) {


    weights = new SynapseLayer * [params->length - 1];
    networkLength = params->length;

    myParams = params;

    for (int i = 0; i < params->length - 1; ++i) {
        weights[i] = new SynapseLayer(params->neuronCounts[i], params->neuronCounts[i + 1]);
    }


    /*
     * multiplyMatricesLength is the length of the longest array,
     * that will be needed in the matrix multiplication
     */
    multiplyMatricesLength = params->neuronCounts[0];
    for (int j = 1; j < params->length; ++j) {
        if(params->neuronCounts[j] > multiplyMatricesLength)
            multiplyMatricesLength = params->neuronCounts[j];
    }

    resultMatrix = new double[multiplyMatricesLength];
    bufferMatrix = new double[multiplyMatricesLength];
}

NeuralNet::~NeuralNet() {

    delete resultMatrix;
    delete bufferMatrix;

    for (int i = 0; i < networkLength; ++i) {
        delete weights[i];
    }

    delete weights;

}

/*
 * The processing algorithm is the hardest thing here,
 * but it's really just matrix multiplications
 */
double * NeuralNet::process(const double *data) {

    /*
     * First we copy the input data to the buffer array,
     * so we can write a single loop that uses:
     * weights, bufferMatrix and resultMatrix
     *
     * (with a bit of magic)
     */

    for (int i = 0; i < weights[0]->getColumns(); ++i) {
        bufferMatrix[i] = data[i];
    }

    for (int layerNumber = 0; layerNumber < networkLength - 1; ++layerNumber) {

        /*
         * Then we empty the resultMatrix,
         * there probably is some old data inside
         */
        fillResultMatrixWith(0);
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                resultMatrix[rowNumber] += bufferMatrix[columnNumber] * weights[layerNumber]->getElement(columnNumber, rowNumber);

            }

        }

        applyFunctionToResultMatrix(sigmoid);

        /*
         * result is copied to buffer and used as input for next layer
         */
        copyResultToBuffer();
    }

    return resultMatrix;
}

void NeuralNet::copyResultToBuffer(){

    for (int i = 0; i < multiplyMatricesLength; ++i) {
        bufferMatrix[i] = resultMatrix[i];
    }

}

void NeuralNet::applyFunctionToResultMatrix(double (*function)(double)) {

    for (int i = 0; i < multiplyMatricesLength; ++i) {
        resultMatrix[i] = function(resultMatrix[i]);
    }

}

void NeuralNet::fillResultMatrixWith(double value) {
    for (int i = 0; i < multiplyMatricesLength; ++i) {
        resultMatrix[i] = value;
    }

}


void NeuralNet::randomizeByPercent(double percent) {

    for (int layerNumber = 0; layerNumber < networkLength - 1; ++layerNumber) {
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                if(generator.generate() < percent) {

                    /*
                     * This mutates a random element
                     */
                    weights[layerNumber]->setElement(columnNumber, rowNumber, SynapseLayer::getRandomNetworkWeight());
                }

            }
        }

    }

 }

NeuralNet::NeuralNet(NeuralNet *parent) :  NeuralNet(parent->myParams) {


    getWeightsFromParent(parent);

}

void NeuralNet::getWeightsFromParent(NeuralNet *parent) {

    /*
     * Copying the weights contents
     */

    for (int layerNumber = 0; layerNumber < networkLength - 1; layerNumber++) {
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                /*
                 * This part looks pretty ugly,
                 * But it's just copying each corresponding weight
                 * to the other network
                 */
                this->weights[layerNumber]->setElement(
                        columnNumber,
                        rowNumber,
                        parent->weights[layerNumber]->getElement(
                                columnNumber,
                                rowNumber
                        )
                );



            }
        }
    }
}

void NeuralNet::saveToFile(std::string filename) {

    fstream outFile;
    outFile.open(filename, std::ios::out);

    if(outFile.good() != true)
        exit(1);

        for (int layerNumber = 0; layerNumber < networkLength - 1; layerNumber++) {
            for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
                for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                    outFile << this->weights[layerNumber]->getElement(columnNumber, rowNumber) << endl;
                }
            }
        }

    outFile.close();
}

void NeuralNet::loadFromFile(std::string filename) {

    fstream inFile;
    inFile.open(filename, std::ios::in);

    double valueReadFromFile = 0;

    if(inFile.good() != true) {
        cout << "Loading failed! Exiting.." << endl;
        exit(1);
    }

        for (int layerNumber = 0; layerNumber < networkLength - 1; layerNumber++) {
            for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
                for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                    inFile >> valueReadFromFile;
                    this->weights[layerNumber]->setElement(columnNumber, rowNumber, valueReadFromFile);
                }
            }
        }

        inFile.close();

}

void NeuralNet::saveToArchive() {

    string filename = "archive/" + getCurrentTime() + ".network";

    this->saveToFile(filename);
}
