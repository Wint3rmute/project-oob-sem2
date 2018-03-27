//
// Created by wint3rmute on 3/6/18.
//

#include <iostream>
#include "../headers/Gun.h"
#include "../headers/GameEngine.h"
#include "../headers/Bullet.h"


void Gun :: activate(Plane & plane)
{

    if(!isOnCooldown())
    {
        setCooldownTime(PISTOL_SHOOT_RATE);

        Bullet *bullet = new Bullet(
                    plane.getPosition().x,
                    plane.getPosition().y,
                    plane.getRotation());

        GameEngine::addObject(bullet);
        current_ammo--;

        if(current_ammo==0)
        {
            setCooldownTime(PISTOL_COOLDOWN_TIME);
            current_ammo=PISTOL_AMMO;
        }
        startCooldown();

    }
}
bool Gun :: isOnCooldown()
{
    return false;
    return cooldown.getElapsedTime().asSeconds()<cooldownTime;
}
