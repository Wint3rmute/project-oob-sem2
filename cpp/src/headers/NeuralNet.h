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

/**
 * @brief A fancy name for a matrix multiplication algorithm
 *
 * Also, controller for planes
 */
class NeuralNet {

    /**
     * @brief All the network weights are stored there
     */
    SynapseLayer ** weights;

    /**
     * @brief NetworkParams describe the structure of the network:
     * depth and number of neurons inside each layer
     */
    NetworkParams * myParams;

    /**
     * @name Properties used for calculating the network output
     * resultMatrix and bufferMatrix are used for matrix multiplication.
     */
     ///@{
    double * resultMatrix;
    double * bufferMatrix;
    int multiplyMatricesLength;
    int networkLength;
    ///@}
    /**
     * @brief Generator used for generating random events when given a probability
     *
     * used for random network mutations
     * generates numbers from 0 to 1
     */
    RandomGenerator generator;


public:
    /**
     * @brief Constructs a neural network given the parameters
     * @param params @see NetworkParams
     */
    explicit NeuralNet(NetworkParams * params);

    /**
     * @brief Constructs a neural network given its parent
     */
    NeuralNet(NeuralNet * parent);

    /**
     * @Process given input data
     *
     * @param data - must be the lenght of the first network layer - the input layer
     */
    double * process(const double * data);

private:

    /**
     * @brief applies a given function to the result matrix
     */
    void applyFunctionToResultMatrix(double (*function)(double));


    /**
     * @name Helpers for the matrix multiplication algorithm
     */
     ///@{

    /**
     * @brief Used for copying a network weights into another network
     *
     */
    void getWeightsFromParent(NeuralNet * parent);

    /**
     * @brief Copies the resultMatrix to the bufferMatrix
     */
    void copyResultToBuffer();
    /**
     * @brief Fills the result matrix with a given value
     * @param value value to fill the result matrix with
     */
    void fillResultMatrixWith(double value);
    ///@}

public:


    /**
     * @brief Method for mutating the network
     *
     * @param percent the percentage of the network that will be changed
     */
    void randomizeByPercent(double percent);

    /**
     * @name Functions for to save/load network from the hard drive
     */
    ///@{
    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    /**
     * @brief saves the network to ./archive folder
     *
     * Network is saved with the timestamp <"%d_%m___%I_%M_%S">
     * and extension .network
     *
     * For example:
     * 0205__143412.network
     * indicates, that a network was saved at the 2nd of May at 14:34 and 12 seconds
     */
    void saveToArchive();
    ///@}

    ~NeuralNet();

};


#endif //PROJECT_NEURALNET_H
