
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/NeuralNet.h"
#include "headers/NeuralController.h"
#include "headers/GameManager.h"


#include <iostream>
#include <ctime>


int main(int argc, char* argv[])
{


    GameManager gm;

    gm.runTheGame(argc, argv);



    return 0;
}
