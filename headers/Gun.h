//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_GUN_H
#define PROJECT_GUN_H


class Plane;

#include "Skill.h"
#include "../utils/constants.h"


class Gun : public Skill {
private:

    int ammunition = PISTOL_AMMO;
    double cooldownTime = PISTOL_SHOOT_RATE;
    int current_ammo = PISTOL_AMMO;

public:
    void activate(Plane & plane);

    bool isOnCooldown();


};


#endif //PROJECT_GUN_H
