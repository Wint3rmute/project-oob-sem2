
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/NeuralNet.h"

#include <iostream>


using namespace std; //I'm going to hell for this

int main()
{

/*
=======
#include "headers/FieldOfView.h"
#include <iostream>

using namespace std;

int main()
{
>>>>>>> 6ea3f5c4b1c1c52b9963b5a59e2de63cca928454
    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Plane * plane2 = new Plane(400, 100, 90);

    FieldOfView * fov = new FieldOfView(plane, VISUAL_CELLS_COUNT);

    KeyboardController *keyboardController = new KeyboardController(plane);
    DummyController *keyboardController2 = new DummyController(plane2);
    keyboardController->changeKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);

    GameEngine::addController(keyboardController);
    GameEngine::addController(keyboardController2);
    GameEngine::addObject(plane);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov);
    //std::cout<<GameEngine::getDistance(plane, plane2);
    //GameEngine::removeObject(bullet);



    GameEngine::play();
    */

    NetworkParams params;

    params.length = 3;
    params.neuronCounts = new int [2];
    params.neuronCounts[0] = 2;
    params.neuronCounts[1] = 3;
    params.neuronCounts[2] = 3;

    NeuralNet a(&params);



    double * data = new double[2];
    data[0] = 0.12;
    data[1] = -0.654;
    data[2] = 0.61;
    a.process(data);

    return 0;
}
