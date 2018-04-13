//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_SKILL_H
#define PROJECT_SKILL_H


#include "Plane.h"
class Plane;

/*
 * Base class for every plane ability such as boost and gun
 */
class Skill {

protected:


    double cooldownTime;

    sf::Clock cooldown;

public:



    double getCooldownTime();


    void setCooldownTime(double t);

    bool isOnCooldown();

    void startCooldown();

    void resetCooldown();

    virtual void activate(Plane & plane) = 0;
};



#endif //PROJECT_SKILL_H
