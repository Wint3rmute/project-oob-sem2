//
// Created by wint3rmute on 3/16/18.
//

#include "../implementations/SynapseLayer.h"

#include <iostream>

#include <random>
#include <iostream>
using namespace std;

SynapseLayer::SynapseLayer(int columns, int rows) {

    std::uniform_real_distribution<double> unif(-1.0, 1.0);
    std::default_random_engine re;

    this->columns = columns;
    this->rows = rows;

    values = new double * [columns];

    for (int i = 0; i < columns; ++i) {
        values[i] = new double[rows];

        for(int z = 0; z < rows; z++)
        {
            values[i][z] = unif(re);
            cout << values[i][z] << endl;
        }

    }
}


SynapseLayer::~SynapseLayer() {

    for (int i = 0; i < columns; ++i)
        delete values[i];


    delete values;
}

double SynapseLayer::getElement(const int & column, const int & row){
    return values[column][row];
}

int SynapseLayer::getColumns() {
    return columns;
}

int SynapseLayer::getRows() {
    return rows;
}
