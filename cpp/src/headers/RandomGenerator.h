//
// Created by wint3rmute on 3/29/18.
//

#ifndef PROJECT_RANDOMGENERATOR_H
#define PROJECT_RANDOMGENERATOR_H

#include <chrono>
#include <random>

/**
 * @brief helper class for generating random numbers,
 *
 * used all across the code to (no surprise) generate random numbers
 */
class RandomGenerator {
    std::default_random_engine rng;
    std::uniform_real_distribution<double> dist;
public:
    /**
     * @brief Creates a random generator with given the maximum and minimum value
     */
    RandomGenerator(double min, double max);

    /**
     * @brief Get a random number
     * @return the random number generated
     */
    double generate();
};


#endif //PROJECT_RANDOMGENERATOR_H
