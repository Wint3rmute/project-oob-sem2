#include "utils/constants.h"
#include "headers/Plane.h"
#include <ctime>

using namespace std;

class Skill {

protected:


  float cooldownTime;
  clock_t actualCooldown;

public:

  float getCooldownTime();

  clock_t getActualCooldown();

  void setActualCooldown(clock_t);

  void setCooldownTime(float);

  bool isOnCooldown();

  void startCooldown();

  void resetCooldown();

  void activate(Plane);
};
