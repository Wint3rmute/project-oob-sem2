//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/Gun.h"
#include "../headers/GameEngine.h"
#include "../headers/Bullet.h"


void Gun :: activate(Plane & plane)
{

    Bullet * bullet = new Bullet(
            plane.getPosition().x,
            plane.getPosition().y,
            plane.getRotation());

    GameEngine::addObject(bullet);

}

