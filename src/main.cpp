
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

    params.length = 3;
    params.neuronCounts = new int [3];

    params.neuronCounts[0] = VISUAL_CELLS_COUNT * 2;
    params.neuronCounts[1] = VISUAL_CELLS_COUNT;
    params.neuronCounts[2] = 2;

    /*
    Plane * plane1 = new Plane(100, 100, 0);
    Plane * plane2 = new Plane(400, 100, 180);


    FieldOfView * fov1 = new FieldOfView(plane1, VISUAL_CELLS_COUNT);
    FieldOfView * fov2 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);


    NeuralController * controller1 = new NeuralController(&params, plane1, fov1);
    NeuralController * controller2 = new NeuralController(&params, plane2, fov2);


    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov1);
    GameEngine::addObject(fov2);


    GameEngine::addController(controller1);
    GameEngine::addController(controller2);
    */

    Plane * plane1 = new Plane(100, 100, 0);
    FieldOfView * fov1 = new FieldOfView(plane1, VISUAL_CELLS_COUNT);
    NeuralController * controller1 = new NeuralController(&params, plane1, fov1);
    GameEngine::addObject(plane1);
    GameEngine::addObject(fov1);
    GameEngine::addController(controller1);


    GameEngine::play();

    controller1->saveToFile("beka.network");

    GameEngine::removeObject(plane1);
    GameEngine::removeObject(fov1);
    GameEngine::removeController(controller1);

    /////////////////////////////////////////////////////////

    Plane * plane2 = new Plane(100, 100, 0);
    FieldOfView * fov2 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);
    NeuralController * controller2 = new NeuralController(&params, plane2, fov2);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov2);
    GameEngine::addController(controller2);

    controller2->loadFromFile("beka.network");

    GameEngine::play();


    return 0;
}
