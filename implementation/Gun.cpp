#include "headers/skills/Gun.h"
#include "headers/Bullet.h"
#include "headers/GameEngine.h"

void Gun :: activate()
{

  Bullet * bullet =  new Bullet(0,0,45);//new Bullet( plane.getPosition().x, plane.getPosition().y, plane.getRotation());
  GameEngine::addObject(bullet);

}
