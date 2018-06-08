
#include "headers/Plane.h"
#include "headers/Bullet.h"
#include "headers/KeyboardController.h"
#include "headers/DummyController.h"
#include "headers/NeuralNet.h"
#include "headers/NeuralController.h"
#include "headers/GameManager.h"


#include <iostream>
#include <ctime>

/*! \mainpage Temat projektu: Trenowanie sieci neuronowych w grze zręcznościowej
 *
 * Autorzy:
 * - Szymon Filipiak
 * - Mateusz Bączek
 *
 * W4 Informatyka, semestr letni 2017-2018
 *
 * Szczegółowy opis projektu zawarty jest w sprawozdaniu.
 */


int main(int argc, char* argv[])
{


    GameManager gm;

    gm.runTheGame(argc, argv);



    return 0;
}
