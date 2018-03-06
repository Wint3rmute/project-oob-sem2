//
// Created by wint3rmute on 3/6/18.
//

#include <ctime>
#include "../headers/Skill.h"

float Skill :: getCooldownTime()
{
    return  cooldownTime;
}

clock_t Skill :: getActualCooldown()
{
    return actualCooldown;
}

void Skill :: setActualCooldown(clock_t t)
{
    actualCooldown = t;
}

void Skill :: setCooldownTime(float t)
{
    cooldownTime = t;
}

bool Skill :: isOnCooldown()
{
    return (((float) getActualCooldown() / CLOCKS_PER_SEC ) - getCooldownTime()) > 0;
}

void Skill :: startCooldown()
{

    setActualCooldown(clock());

}

void Skill :: resetCooldown()
{



}
