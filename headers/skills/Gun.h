#include "headers/Skill.h"
#include "headers/Bullet.h"

class Gun : public Skill
{
private:

  int ammunition = PISTOL_AMMO;
  float cooldownTime = PISTOL_COOLDOWN_TIME;

public:

  void activate(Plane);


};
