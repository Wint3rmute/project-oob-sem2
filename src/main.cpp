
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/FieldOfView.h"
#include <iostream>
int main()
{


    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Plane * plane2 = new Plane(400, 100, 90);

    FieldOfView * fov = new FieldOfView(plane, VISUAL_CELLS_COUNT);

    KeyboardController *keyboardController = new KeyboardController(plane);
    DummyController *keyboardController2 = new DummyController(plane2);
    keyboardController->changeKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);

    GameEngine::addObject(fov);
    GameEngine::addController(keyboardController);
    GameEngine::addController(keyboardController2);
    GameEngine::addObject(plane);
    GameEngine::addObject(plane2);
    //std::cout<<GameEngine::getDistance(plane, plane2);
    //GameEngine::removeObject(bullet);



    GameEngine::play();
    return 0;
}
