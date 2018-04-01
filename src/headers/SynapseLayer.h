//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_SYNAPSELAYER_H
#define PROJECT_SYNAPSELAYER_H


#include <random>
#include "RandomGenerator.h"

class SynapseLayer {

    /*
     * 2dimensional array of doubles, stores the matrix values
     */
    double ** values;

    /*
     * Saving the size of the matrix
     */
    int columns, rows;
    static RandomGenerator generator;

    /*
     * Used for random weights generation
     */
    static std::uniform_real_distribution<double> uniform_real_distribution;
    static std::default_random_engine random_engine;


public:

    /*
     * Get a random weight between -1.0 and 1.0
     */
    static double getRandomNetworkWeight();
    /*
     * Generates an empty matrix of a given size
     */
    SynapseLayer(int columns, int rows);

    /*
     * Returns an element at given indexes
     */
    double getElement(const int& column, const int& row);

    /*
     * Sets a value for an element given its indexes
     */
    void setElement(const int& column, const int& row, const double & value);

    /*
     * Get amount of columns
     */
    int getColumns();

    /*
     * Get amount of rows
     */
    int getRows();


    ~SynapseLayer();
};


#endif //PROJECT_SYNAPSELAYER_H
