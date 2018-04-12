//
// Created by wint3rmute on 3/16/18.
//

#include "../headers/NeuralNet.h"

#include <iostream>
using namespace std;


double sigmoid(double value)
{
    //cout << 1.0 / ( 1.0 + exp(-value) ) << endl;
    return 1.0 / ( 1.0 + exp(-value) );
}


/*
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

NeuralNet::NeuralNet(NetworkParams * params) : generator(0, 1.0) {


    
    weights = new SynapseLayer * [params->length - 1];
    networkLength = params->length;

    myParams = params;

    for (int i = 0; i < params->length - 1; ++i) {
        weights[i] = new SynapseLayer(params->neuronCounts[i], params->neuronCounts[i + 1]);
    }


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
 * so let's make it as simple and as efficient as possible
 *
 * (and also lets write it in a reasonable time)
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
         * Yup, making the result matrix an empty matrix
         * seems like a good idea
         */
        fillResultMatrixWith(0);
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                resultMatrix[rowNumber] += bufferMatrix[columnNumber] * weights[layerNumber]->getElement(columnNumber, rowNumber);

            }

        }

        applyFunctionToResultMatrix(sigmoid);
        //cout << resultMatrix[0] << endl;
        copyResultToBuffer();
    }

    //cout << resultMatrix[0] << endl;
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
                    //cout << "mutation" << layerNumber << " " << columnNumber << " " << rowNumber << endl;
                    weights[layerNumber]->setElement(columnNumber, rowNumber, SynapseLayer::getRandomNetworkWeight());
                }

            }
        }

        applyFunctionToResultMatrix(sigmoid);
        copyResultToBuffer();
    }
}

NeuralNet::NeuralNet(NeuralNet *parent) :  NeuralNet(parent->myParams) {

    /*
    this->myParams = parent->myParams;
    this->networkLength = parent->myParams->length;
     */

    getWeightsFromParent(parent);
}

void NeuralNet::getWeightsFromParent(NeuralNet *parent) {

    /*
 * Copying the weights contents
 */
    //cout << "GETTING WEIGHTS FROM PARENT" << endl;
    for (int layerNumber = 0; layerNumber < networkLength - 1; layerNumber++) {
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                /*
                 * I know it looks terrifying
                 * But it's just copying each corresponding weight
                 */
                this->weights[layerNumber]->setElement(
                        columnNumber,
                        rowNumber,
                        parent->weights[layerNumber]->getElement(
                                columnNumber,
                                rowNumber
                        )
                );
                //cout << layerNumber << " " << rowNumber << " " << columnNumber << endl;


            }
        }
    }
    //cout << "WEIGHTS COPIED" << endl;
}

void NeuralNet::saveToFile(std::string filename) {

    fstream outFile;
    outFile.open(filename, std::ios::out);

    if(outFile.good() != true)
        exit(2137);

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

    if(inFile.good() != true)
        exit(1337);

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
