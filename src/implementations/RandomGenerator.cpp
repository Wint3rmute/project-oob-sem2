//
// Created by wint3rmute on 3/29/18.
//

#include "../headers/RandomGenerator.h"

RandomGenerator::RandomGenerator(double min, double max) {

    this->min = min;
    this->max = max;

}

/*
 * TODO: ACTUALLY UNDERSTAND THIS CODE FROM STACKOVERFLOW
 */
double RandomGenerator::generate() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(min, max);

    return dis(gen) ; //Each call to dis(gen) generates a new random double

}
