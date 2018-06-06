//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_GUN_H
#define PROJECT_GUN_H


class Plane;

#include "Skill.h"
#include "../utils/constants.h"

/**
 * @brief A skill that allows to shoot bullets
 */
class Gun : public Skill {
private:

    int current_ammo = PISTOL_AMMO;


public:
    /**
     * @brief Gun activation function
     * Gun activation function. Spawns bullets as long as there is ammo in the gun, then starts cooldown.
     * @param plane Plane in front of which bullets appear
     */
    void activate(Plane & plane);


};


#endif //PROJECT_GUN_H
