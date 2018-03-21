//
// Created by wint3rmute on 3/16/18.
//

#ifndef PROJECT_SYNAPSELAYER_H
#define PROJECT_SYNAPSELAYER_H


class SynapseLayer {

    double ** values;
    int columns, rows;


public:

    /*
     * Generates an empty matrix of a given size
     */
    SynapseLayer(int columns, int rows);
    double getElement(const int& column, const int& row);
    int getColumns();
    int getRows();


    ~SynapseLayer();
};


#endif //PROJECT_SYNAPSELAYER_H
