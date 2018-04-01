//
// Created by wint3rmute on 3/16/18.
//

#include "../headers/SynapseLayer.h"
#include <iostream>

using namespace std;

RandomGenerator SynapseLayer::generator(-1.0, 1.0);

SynapseLayer::SynapseLayer(int columns, int rows) {

    this->columns = columns;
    this->rows = rows;

    values = new double * [columns];

    for (int i = 0; i < columns; ++i) {
        values[i] = new double[rows];

        for(int z = 0; z < rows; z++)
        {
            values[i][z] = getRandomNetworkWeight();
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

void SynapseLayer::setElement(const int &column, const int &row, const double &value) {
    values[column][row] = value;
}

double SynapseLayer::getRandomNetworkWeight() {
    generator.generate();
}
