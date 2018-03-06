
#include "headers/Plane.h"
#include "headers/Bullet.h"

int main()
{


    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Bullet * bullet = new Bullet(50,50,45);

    GameEngine::addObject(plane);
    GameEngine::addObject(bullet);
    //GameEngine::removeObject(bullet);
    GameEngine::play();

    return 0;
}
