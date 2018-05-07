//
// Created by wint3rmute on 4/12/18.
//

#ifndef PROJECT_GAMEMANAGER_H
#define PROJECT_GAMEMANAGER_H


#include "../utils/structs.h"
#include "../utils/constants.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Sets parameters for the GameEngine and runs the game accordingly to the users input parameters
 */
class GameManager {

    /*
     * command line arguments,
     * will be used to launch the game with certain objects and options
     */
    std::string argument1;
    std::string argument2;

    /*
     * NetworkParams for all the neural nets in the game
     */
    NetworkParams params;


public:
    GameManager();

    /*
     * Lets the program react to a ctrl+c signal
     * display an info message before exiting
     */
    void enableSignalCatching();

    /*
     * takes the command arguments and runs the game accordingly
     */
    void runTheGame(int argc, char* argv[]);

    /*
     * The functions below are used for launching various game modes that can be chosen by command line arguments
     *
     * their names are self-explanatory
     */

    void showHelpMessage();

    void playGame2Players();

    void playVsBestAI();

    void trainVisible();
    void trainInvisible();

    void trainVisibleContinue();
    void trainInvisibleContinue();

    void playVsLoadedAI();

};


#endif //PROJECT_GAMEMANAGER_H
