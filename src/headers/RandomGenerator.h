//
// Created by wint3rmute on 3/29/18.
//

#ifndef PROJECT_RANDOMGENERATOR_H
#define PROJECT_RANDOMGENERATOR_H


#include <random>

/*
 * TODO: MAKE THIS EFFICIENT
 * not shamelessly copied
 */
class RandomGenerator {
    double min,max;

public:
    RandomGenerator(double min, double max);
    double generate();
};


#endif //PROJECT_RANDOMGENERATOR_H
