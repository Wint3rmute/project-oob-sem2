//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_NEURALNET_H
#define PROJECT_NEURALNET_H

#include "SynapseLayer.h"
#include "../utils/structs.h"
#include "RandomGenerator.h"
#include <cmath>


/*
 * That's just a fancy name for a matrix multiplication algorithm
 */
class NeuralNet {

    /*
     * Used for random weights generation
     */
    static std::uniform_real_distribution<double> uniform_real_distribution;
    static std::default_random_engine random_engine;

    SynapseLayer ** weights;
    NetworkParams * myParams;

    /*
     * Calling them matrices is kinda too much.. those are only 1 x n vectors
     * (But cmon, buzzwords)
     */
    double * resultMatrix;
    double * bufferMatrix;
    int networkLength;
    int multiplyMatricesLength;

    RandomGenerator generator;

public:
    /*
     * Yes
     */
    explicit NeuralNet(NetworkParams * params) : generator(0.0, 1.0);//TODO FIX

    /*
     * Process the data, without checking the array length,
     * who needs safety anyway
     */
    const double * process(const double * data);
    void applyFunctionToResultMatrix(double (*function)(double));

    NeuralNet operator* (float x);

    void copyResultToBuffer();
    void fillResultMatrixWith(double value);

    void randomizeByPercent(double percent);

    ~NeuralNet();

};


#endif //PROJECT_NEURALNET_H
