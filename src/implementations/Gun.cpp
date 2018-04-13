//
// Created by wint3rmute on 3/6/18.
//

#include <iostream>
#include "../headers/Gun.h"
#include "../headers/GameEngine.h"
#include "../headers/Bullet.h"

using namespace std;
/*
*On activation creates new Bullet instanes with plane properties. 
*
*Bullets are spawned untill ammunition is gone.
*/
void Gun :: activate(Plane & plane)
{

    if(!isOnCooldown())
    {
        setCooldownTime(PISTOL_SHOOT_RATE);
        startCooldown();

        Bullet *bullet = new Bullet(
                    plane.getPosition().x,
                    plane.getPosition().y,
                    plane.getRotation());

        GameEngine::addObject(bullet);
        current_ammo--;

        if(current_ammo==0)
        {
            setCooldownTime(PISTOL_COOLDOWN_TIME);
            startCooldown();
            current_ammo=PISTOL_AMMO;
        }
        startCooldown();

    }
}

