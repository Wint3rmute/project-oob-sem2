//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_SYNAPSELAYER_H
#define PROJECT_SYNAPSELAYER_H


#include <random>
#include "RandomGenerator.h"

/**
 * @brief A single weights matrix between network layers
 *
 * The class handles storage of the network weights inside RAM,
 * as well as generation of new random synapse weights.
 *
 */
class SynapseLayer {


    /**
     * @brief 2dimentional array storing the weights
     */
    double ** values;


    /**
     * @brief how many columns in the matrix
     */
    int columns;

    /**
     * @brief how many rows in the matrix
     */
    int rows;

    /**
     * @brief generator for the weight values
     *
     * Generates numbers between -1 and 1
     *
     */
    static RandomGenerator generator;



public:

    /**
     * Get a random weight between -1.0 and 1.0
     */
    static double getRandomNetworkWeight();
    /**
     * Generates an empty matrix of a given size

      * @param columns amount of columns
      * @param rows amount of rows
      */
    SynapseLayer(int columns, int rows);

    /**
     * Returns an element at given indexes
     */
    double getElement(const int& column, const int& row);

    /**
     * Sets a value for an element given its indexes
     */
    void setElement(const int& column, const int& row, const double & value);

    /**
     * Get amount of columns
     */
    int getColumns();

    /**
     * Get amount of rows
     */
    int getRows();


    ~SynapseLayer();
};


#endif //PROJECT_SYNAPSELAYER_H
