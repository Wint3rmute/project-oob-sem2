
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"

int main()
{


    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Plane * plane2 = new Plane(50, 100, 90);

    KeyboardController *keyboardController = new KeyboardController(plane);
    KeyboardController *keyboardController2 = new KeyboardController(plane2);

    GameEngine::addController(keyboardController);
    GameEngine::addController(keyboardController2);
    GameEngine::addObject(plane);
    GameEngine::addObject(plane2);
    //GameEngine::removeObject(bullet);
    GameEngine::play();
    return 0;
}
