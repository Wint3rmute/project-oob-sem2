//
// Created by wint3rmute on 3/29/18.
//

#include "../headers/RandomGenerator.h"

RandomGenerator::RandomGenerator(double min, double max)
        : rng(static_cast<unsigned long>(
                      std::chrono::system_clock::now().time_since_epoch().count()
              )),
          dist(min,max){}

/*
 * TODO: ACTUALLY UNDERSTAND THIS CODE FROM STACKOVERFLOW
 */
double RandomGenerator::generate() {

    return dist(rng);
}
