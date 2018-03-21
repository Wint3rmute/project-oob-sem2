//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_NEURALNET_H
#define PROJECT_NEURALNET_H

#include "../implementations/SynapseLayer.h"
#include "../utils/structs.h"


/*
 * That's just a fancy name for a matrix multiplication algorithm
 */
class NeuralNet {

    SynapseLayer ** weights;

    /*
     * Calling them matrices is kinda too much.. those are only 1 x n vectors
     * (But cmon, buzzwords)
     */
    double * resultMatrix;
    double * bufferMatrix;
    int networkLength;
    int multiplyMatricesLength;

public:
    /*
     * Yes
     */
    explicit NeuralNet(NetworkParams params);

    /*
     * Process the data, without checking the array length,
     * who needs safety anyway
     */
    double process(double * data);
    void applyFunctionToResultMatrix(double (*function)(double));

    void copyResultToBuffer();
    void fillResultMatrixWith(double value);
    ~NeuralNet();

};


#endif //PROJECT_NEURALNET_H
