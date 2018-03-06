//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_SKILL_H
#define PROJECT_SKILL_H


#include "Plane.h"
class Plane;

class Skill {

protected:


    float cooldownTime;
    clock_t actualCooldown;

public:

    float getCooldownTime();

    clock_t getActualCooldown();

    void setActualCooldown(clock_t t);

    void setCooldownTime(float t);

    bool isOnCooldown();

    void startCooldown();

    void resetCooldown();

    virtual void activate(Plane & plane) = 0;
};



#endif //PROJECT_SKILL_H
