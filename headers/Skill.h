#pragma once
#include "utils/constants.h"
//#include "headers/Plane.h"
#include <ctime>
class Plane;

using namespace std;

class Skill {

protected:


  float cooldownTime;
  clock_t actualCooldown;

public:

  float getCooldownTime();

  clock_t getActualCooldown();

  void setActualCooldown(clock_t t);

  void setCooldownTime(float t);

  bool isOnCooldown();

  void startCooldown();

  void resetCooldown();

  virtual void activate(Plane & plane) = 0;
};
