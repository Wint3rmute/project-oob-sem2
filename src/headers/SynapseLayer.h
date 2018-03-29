//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_SYNAPSELAYER_H
#define PROJECT_SYNAPSELAYER_H


#include <random>

class SynapseLayer {

    double ** values;
    int columns, rows;

    static std::uniform_real_distribution<double> unif;
    static std::default_random_engine re;


public:

    /*
     * Generates an empty matrix of a given size
     */
    SynapseLayer(int columns, int rows);
    double getElement(const int& column, const int& row);
    void setElement(const int& column, const int& row, const double & value);
    int getColumns();
    int getRows();

    static double getRandomWeight();


    ~SynapseLayer();
};


#endif //PROJECT_SYNAPSELAYER_H
