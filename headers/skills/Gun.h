#pragma once
#include "headers/Skill.h"
#include "headers/Bullet.h"
#include "headers/Plane.h"

class Gun : public Skill
{
private:

  int ammunition = PISTOL_AMMO;
  float cooldownTime = PISTOL_COOLDOWN_TIME;

public:

  void activate(Plane & plane);


};
