
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
    params.neuronCounts[1] = VISUAL_CELLS_COUNT * 3;
    params.neuronCounts[2] = VISUAL_CELLS_COUNT;
    params.neuronCounts[3] = 2;

    Plane * plane1 = new Plane(100, 100, 0);
    Plane * plane2 = new Plane(400, 100, 180);
    Plane * plane3 = new Plane(400, 500, 0);
    Plane * plane4 = new Plane(400, 500, 180);

    FieldOfView * fov1 = new FieldOfView(plane1, VISUAL_CELLS_COUNT);
    FieldOfView * fov2 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);
    FieldOfView * fov3 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);
    FieldOfView * fov4 = new FieldOfView(plane2, VISUAL_CELLS_COUNT);

    NeuralController * controller1 = new NeuralController(&params, plane1, fov1);
    NeuralController * controller2 = new NeuralController(&params, plane2, fov2);
    NeuralController * controller3 = new NeuralController(&params, plane3, fov3);
    NeuralController * controller4 = new NeuralController(&params, plane4, fov3);

    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);
    GameEngine::addObject(plane3);
    GameEngine::addObject(plane4);

    GameEngine::addObject(fov1);
    GameEngine::addObject(fov2);
    GameEngine::addObject(fov3);
    GameEngine::addObject(fov4);

    GameEngine::addController(controller1);
    GameEngine::addController(controller2);
    GameEngine::addController(controller3);
    GameEngine::addController(controller4);

    GameEngine::play();


    return 0;
}
