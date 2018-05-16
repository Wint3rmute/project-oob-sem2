//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_GUN_H
#define PROJECT_GUN_H


class Plane;

#include "Skill.h"
#include "../utils/constants.h"

/**
 * A skill that allows to shoot bullets
 */
class Gun : public Skill {
private:

    int current_ammo = PISTOL_AMMO;


public:
    void activate(Plane & plane);


};


#endif //PROJECT_GUN_H
