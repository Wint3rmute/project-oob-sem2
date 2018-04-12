//
// Created by wint3rmute on 4/12/18.
//

#include <iostream>
#include "../headers/GameManager.h"

GameManager::GameManager() {

    argument1 = "";
    argument2 = "";

    /*
     * This is a global setting
     *
     * Do. Not. Touch.
     * DON'T.
     */
    params.length = 3;
    params.neuronCounts = new int [3];

    params.neuronCounts[0] = VISUAL_CELLS_COUNT * 2;
    params.neuronCounts[1] = VISUAL_CELLS_COUNT;
    params.neuronCounts[2] = 2;


}

void GameManager::runTheGame(int argc, char **argv) {

    if(argc < 2){
        showHelpMessage();
        return;
    }


    argument1 = argv[1];

    if(argc > 2)
    argument2 = argv[2];


    if(argument1 == "--help")
        showHelpMessage();

    else if(argument1 == "--play2")
        playGame2Players();

    else if(argument1 == "--play-ai")
        playVsBestAI();

    else if(argument1 == "--train-visible")
        trainVisible();

    else if(argument1 == "--train-invisible")
        trainInvisible();

    else if(argument1 == "--play-ai-load")
        playVsLoadedAI();
    else
        showHelpMessage();



}


void GameManager::showHelpMessage() {

    std::cout << "Machine Learning Plane Game Experiment \n"
                 "Usage: \n\n"
                 "\t--help - print this help message \n\n"
                 "\t--play2 - 2 planes, both controlled by keyboard, sort of a playground \n"
                 "\t--play-ai - play against the best trained AI available \n\n"
                 "\t--train-visible - show the process of network training \n"
                 "\t--train-invisible - train the networks ASAP, no graphics \n\n"
                 "\t--play-ai-load <filename> play against the AI from the <filename> \n\n";

}

void GameManager::playGame2Players() {
    std::cout << "Playing Human vs Human" << std::endl;

}

void GameManager::playVsBestAI() {
    std::cout << "Playing Human vs Best Avialable AI" << std::endl;

}

void GameManager::trainVisible() {
    std::cout << "Training AI in a visible window" << std::endl;

}

void GameManager::trainInvisible() {
    std::cout << "Training AI ASAP without graphics" << std::endl;
}

void GameManager::playVsLoadedAI() {
    std::cout << "Loading AI from file " + argument2;
}