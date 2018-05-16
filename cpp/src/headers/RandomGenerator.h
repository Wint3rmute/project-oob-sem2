//
// Created by wint3rmute on 3/29/18.
//

#ifndef PROJECT_RANDOMGENERATOR_H
#define PROJECT_RANDOMGENERATOR_H

#include <chrono>
#include <random>

/**
 * helper class for generating random numbers,
 *
 * used all across the code
 */
class RandomGenerator {
    std::default_random_engine rng;
    std::uniform_real_distribution<double> dist;
public:
    RandomGenerator(double min, double max);
    double generate();
};


#endif //PROJECT_RANDOMGENERATOR_H
