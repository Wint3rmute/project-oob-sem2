//
// Created by wint3rmute on 3/6/18.
//

#include <ctime>
#include <iostream>
#include "../headers/Skill.h"
using namespace std;

double Skill :: getCooldownTime()
{
    return  cooldownTime;
}


void Skill :: setCooldownTime(double t)
{
    cooldownTime = t;
}

bool Skill :: isOnCooldown()
{
    return cooldown.getElapsedTime().asSeconds() < cooldownTime;

}

void Skill :: startCooldown()
{

    cooldown.restart();

}

void Skill :: resetCooldown()
{



}
