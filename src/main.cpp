
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include <iostream>
int main()
{


    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Plane * plane2 = new Plane(400, 100, 90);

    KeyboardController *keyboardController = new KeyboardController(plane);
    //KeyboardController *keyboardController2 = new KeyboardController(plane2);
    DummyController *dummyController = new DummyController(plane2);
    keyboardController->changeKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);

    GameEngine::addController(keyboardController);
    GameEngine::addController(dummyController);
    GameEngine::addObject(plane);
    GameEngine::addObject(plane2);
    std::cout<<GameEngine::getDistance(plane, plane2);
    //GameEngine::removeObject(bullet);
    GameEngine::play();
    return 0;
}
