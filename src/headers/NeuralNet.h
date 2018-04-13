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
 * A fancy name for a matrix multiplication algorithm
 */
class NeuralNet {

    /*
     * All the network weights are stored there
     */
    SynapseLayer ** weights;

    /*
     * NetworkParams describe the structure of the network:
     * depth and number of neurons inside each layer
     */
    NetworkParams * myParams;

    /*
     * resultMatrix and bufferMatrix are used for matrix multiplication.
     */
    double * resultMatrix;
    double * bufferMatrix;

    int multiplyMatricesLength;
    int networkLength;

    /*
     * Generator used for generating random events when given a probability
     *
     * used for random network mutations
     */
    RandomGenerator generator;


public:
    explicit NeuralNet(NetworkParams * params);
    NeuralNet(NeuralNet * parent);

    /*
     * Process given data
     */
    double * process(const double * data);

    /*
     * sigmoid activation function will be applied
     */
    void applyFunctionToResultMatrix(double (*function)(double));

    /*
     * Used for copying a network weights into another network
     *
     * 'breeding' nets
     */
    void getWeightsFromParent(NeuralNet * parent);

private:
    /*
     * Helpers for the matrix multiplication algorithm
     */
    void copyResultToBuffer();
    void fillResultMatrixWith(double value);


public:


    /*
     * The mutator function
     */
    void randomizeByPercent(double percent);


    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    void saveToArchive();

    ~NeuralNet();

};


#endif //PROJECT_NEURALNET_H
