//
// Created by wint3rmute on 4/12/18.
//

#ifndef PROJECT_GAMEMANAGER_H
#define PROJECT_GAMEMANAGER_H


#include "../utils/structs.h"
#include "../utils/constants.h"

class GameManager {

    std::string argument1;
    std::string argument2;
    NetworkParams params;


public:
    GameManager();

    void runTheGame(int argc, char* argv[]);

    void showHelpMessage();

    void playGame2Players();
    void playVsBestAI();
    void trainVisible();
    void trainInvisible();
    void playVsLoadedAI();

};


#endif //PROJECT_GAMEMANAGER_H
