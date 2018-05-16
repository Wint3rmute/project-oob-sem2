//
// Created by shiro on 11.04.18.
//

#ifndef PROJECT_BOOST_H
#define PROJECT_BOOST_H

class Plane;
/**
 * @file Boost.h
 * File containing declaration of Boost class
 */

#include "Skill.h"
#include "../utils/constants.h"
/**
 * @brief Boost for plane
 * Skill that boosts plane speed, for a short period of time when used
 */
class Boost : public Skill {
private:
    /**
     * Boost time remaining in seconds
     */
    double boostTimeRemaining=BOOST_DURATION;

public:
    /**
     * @brief Boost activation behaviour
     * Implements behaviour when skill activation happens increasing speed of plane
     * @param plane Plane on witch is used @see Skill
     */
    void activate(Plane & plane);
};

#endif //PROJECT_BOOST_H
