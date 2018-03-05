#ifndef GUN_H
#define GUN_H

#include "headers/Skill.h"
#include "headers/Bullet.h"
#include "headers/Plane.h"
class Gun : public Skill
{
private:

  int ammunition = PISTOL_AMMO;
  float cooldownTime = PISTOL_COOLDOWN_TIME;

public:
  Gun(void);
  void activate(Plane & plane);


};

#endif