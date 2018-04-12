
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/NeuralNet.h"
#include "headers/NeuralController.h"
#include "headers/GameManager.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <ctime>


int main(int argc, char* argv[])
{


    GameManager gm;
    gm.runTheGame(argc, argv);
    //gm.playGame2Players();

    //gm.trainVisible();




    return 0;
}
