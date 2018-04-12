//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_NEURALNET_H
#define PROJECT_NEURALNET_H

#include "SynapseLayer.h"
#include "../utils/structs.h"
#include "RandomGenerator.h"
#include <cmath>
#include <fstream>

/*
 * That's just a fancy name for a matrix multiplication algorithm
 */
class NeuralNet {


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
    explicit NeuralNet(NetworkParams * params); //TODO FIX
    NeuralNet(NeuralNet * parent);

    /*
     * Process the data, without checking the array length,
     * who needs safety anyway
     */
    double * process(const double * data);
    void applyFunctionToResultMatrix(double (*function)(double));

    void getWeightsFromParent(NeuralNet * parent);


    void copyResultToBuffer();
    void fillResultMatrixWith(double value);

    void randomizeByPercent(double percent);

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    void saveToArchive();

    ~NeuralNet();

};


#endif //PROJECT_NEURALNET_H
