//
// Created by shiro on 11.04.18.
//

#ifndef PROJECT_BOOST_H
#define PROJECT_BOOST_H

class Plane;

#include "Skill.h"
#include "../utils/constants.h"

class Boost : public Skill {
private:
    double boostTimeRemaining=BOOST_DURATION;

public:
    void activate(Plane & plane);
};

#endif //PROJECT_BOOST_H
