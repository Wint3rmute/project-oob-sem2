#include "headers/skills/Gun.h"
#include "headers/Bullet.h"

void Gun :: activate(Plane & plane)
{

  Bullet * bullet = new Bullet( plane.getPosition().x, plane.getPosition().y, plane.getRotation());
  GameEngine::addObject(bullet);

}
