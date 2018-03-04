
#include "utils/constants.h"
#include "headers/Skill.h"


using namespace std;

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
  if( (((float) getActualCooldown() / CLOCKS_PER_SEC ) - getCooldownTime()) > 0 )

      return true;

    else

      return false;
}

void Skill :: startCooldown()
{

  setActualCooldown(clock());

}

void Skill :: resetCooldown()
{



}
