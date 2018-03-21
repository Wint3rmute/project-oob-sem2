
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
    //GameEngine engine;
    Plane *plane = new Plane(50, 50, 90);
    Plane * plane2 = new Plane(50, 100, 90);

    KeyboardController *keyboardController = new KeyboardController(plane);
    //KeyboardController *keyboardController2 = new KeyboardController(plane2);
    DummyController *dummyController = new DummyController(plane2);
    keyboardController->changeKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);

    GameEngine::addController(keyboardController);
    GameEngine::addController(dummyController);
    GameEngine::addObject(plane);
    GameEngine::addObject(plane2);
    //GameEngine::removeObject(bullet);
    GameEngine::play();
    */

    NetworkParams params;


    params.length = 2;
    params.neuronCounts = new int [2];
    params.neuronCounts[0] = 2;
    params.neuronCounts[1] = 3;

    NeuralNet a(params);



    double * data = new double[2];
    data[0] = 10;
    data[1] = 20;
    cout << "umm lemme just" << data[1]<< endl;
    a.process(data);

    cout << "Working" << endl;
    return 0;
}
