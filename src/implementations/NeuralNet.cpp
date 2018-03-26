//
// Created by wint3rmute on 3/16/18.
//

#include <cmath>
#include "../headers/NeuralNet.h"

#include <iostream>
using namespace std;

double sigmoid(double value)
{
    //cout << 1.0 / ( 1.0 + exp(-value) ) << endl;
    return 1.0 / ( 1.0 + exp(-value) );
}

NeuralNet::NeuralNet(NetworkParams * params) {
    
    weights = new SynapseLayer * [params->length - 1];
    networkLength = params->length;

    myParams = params;

    for (int i = 0; i < params->length - 1; ++i) {
        weights[i] = new SynapseLayer(params->neuronCounts[i], params->neuronCounts[i+1]);
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
double NeuralNet::process(double *data) {

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
        copyResultToBuffer();
    }

    //cout << "AWAKE AWAKE" << endl;

    /*
    for(int i = 0; i < 3; i++)
        cout << resultMatrix[i] << ", ";
    cout << endl;
    */

    return 0;
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



NeuralNet NeuralNet::operator*(float x) {
    NeuralNet result(myParams);

    /*
     * Copying the weights contents
     */

    for (int layerNumber = 0; layerNumber < networkLength - 1; layerNumber++) {
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                result.weights[layerNumber]. weights[layerNumber]->getElement(columnNumber, rowNumber);

            }

        }



        result.randomizeByPercent(x);

    return result;
}

void NeuralNet::randomizeByPercent(double percent) {

    for (int layerNumber = 0; layerNumber < networkLength - 1; ++layerNumber) {
        for (int rowNumber = 0; rowNumber < weights[layerNumber]->getRows(); ++rowNumber) {
            for (int columnNumber = 0; columnNumber < weights[layerNumber]->getColumns(); ++columnNumber) {

                resultMatrix[rowNumber] += bufferMatrix[columnNumber] * weights[layerNumber]->getElement(columnNumber, rowNumber);

            }

        }

        applyFunctionToResultMatrix(sigmoid);
        copyResultToBuffer();
    }


}
