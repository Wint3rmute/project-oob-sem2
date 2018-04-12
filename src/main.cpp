
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/NeuralNet.h"
#include "headers/NeuralController.h"

#include <iostream>


using namespace std; //I'm going to hell for this

int main()
{

    NetworkParams params;

    params.length = 4;
    params.neuronCounts = new int [4];

    params.neuronCounts[0] = VISUAL_CELLS_COUNT * 2;
    params.neuronCounts[1] = VISUAL_CELLS_COUNT * 1;
    params.neuronCounts[2] = VISUAL_CELLS_COUNT * 0.5f;
    params.neuronCounts[3] = 2;

    Plane * plane1 = new Plane(100, 100, 0);
    Plane * plane2 = new Plane(400, 100, 180);


    FieldOfView * fov1 = new FieldOfView(plane1, VISUAL_CELLS_COUNT);
    FieldOfView * fov2 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);


    KeyboardController *keyboardController = new KeyboardController(plane);
    KeyboardController *keyboardController2 = new KeyboardController(plane2);
    keyboardController->changeKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::W);

    NeuralController * controller1 = new NeuralController(&params, plane1, fov1);
    NeuralController * controller2 = new NeuralController(&params, plane2, fov2);


    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov1);
    GameEngine::addObject(fov2);


    GameEngine::addController(controller1);
    GameEngine::addController(controller2);


    GameEngine::play();


    return 0;
}
