//
// Created by wint3rmute on 4/12/18.
//

#include <iostream>
#include "../headers/GameManager.h"
#include "../headers/GameEngine.h"
#include "../headers/NeuralController.h"
#include "../headers/KeyboardController.h"

GameManager::GameManager() {

    enableSignalCatching();

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
    params.neuronCounts[1] = VISUAL_CELLS_COUNT * 0.5;
    params.neuronCounts[2] = 3;


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

    else if(argument1 == "--train-visible-continue")
        trainVisibleContinue();

    else if(argument1 == "--train-invisible-continue")
        trainInvisibleContinue();

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
                 "\t--train-visible - show the process of network training \n"
                 "\t--train-visible-continue - same as above, but will use the best saved network as a starting point\n\n"
                 "\t--train-invisible - train the networks ASAP, no graphics \n"
                 "\t--train-invisible-continue - same as above, but will use the best saved network as a starting point\n\n"
                 "\t--play-ai - play against the best trained AI available \n"
                 "\t--play-ai-load <filename> play against the AI from the <filename> \n\n";

}

void GameManager::playGame2Players() {

    auto plane1 = new Plane(100, 100, 0);
    auto plane2 = new Plane(800, 100, 180);

    auto keyboardController1 = new KeyboardController(plane1);
    auto keyboardController2 = new KeyboardController(plane2);

    keyboardController2->changeKeys(Key::A, Key::D, Key::S, Key::W);

    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);

    GameEngine::addController(keyboardController1);
    GameEngine::addController(keyboardController2);

    GameEngine::init();
    GameEngine::play();
}

void GameManager::playVsBestAI() {
    std::cout << "Playing against the best avialable AI" << std::endl;

    auto plane1 = new Plane(100, 100, 0);
    auto plane2 = new Plane(800, 100, 180);

    auto keyboardController1 = new KeyboardController(plane1);

    auto fov = new FieldOfView(plane2, VISUAL_CELLS_COUNT);
    auto neuralController = new NeuralController(&params, plane2, fov);
    neuralController->loadFromFile(BEST_NETWORK_FILENAME);


    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov);

    GameEngine::addController(keyboardController1);
    GameEngine::addController(neuralController);

    GameEngine::init();
    GameEngine::play();

}


void GameManager::playVsLoadedAI() {
    std::cout << "Loading AI from file " + argument2 << std::endl;

    auto plane1 = new Plane(100, 100, 0);
    auto plane2 = new Plane(800, 100, 180);

    auto keyboardController1 = new KeyboardController(plane1);

    auto fov = new FieldOfView(plane2, VISUAL_CELLS_COUNT);
    auto neuralController = new NeuralController(&params, plane2, fov);
    neuralController->loadFromFile(argument2);


    GameEngine::addObject(plane1);
    GameEngine::addObject(plane2);
    GameEngine::addObject(fov);

    GameEngine::addController(keyboardController1);
    GameEngine::addController(neuralController);

    GameEngine::init();
    GameEngine::play();

}

void GameManager::trainVisible() {
    std::cout << "Training AI in a visible window" << std::endl;

    auto myPlane = new Plane(100, 100, 0);
    auto myController = new KeyboardController(myPlane);

    GameEngine::addObject(myPlane);
    GameEngine::addController(myController);

    GameEngine::spawnNewRandomAIControlledPlaneInARandomPlace(&params);
    GameEngine::spawnNewRandomAIControlledPlaneInARandomPlace(&params);

    GameEngine::init();
    GameEngine::setVisibility(true);
    GameEngine::setBeforeFrameFunction(
            GameEngine::checkPlanesCountAndSpawnNewPlaneAccordingly
    );

    GameEngine::setAfterFrameFunction(
            GameEngine::checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening
            );

    GameEngine::play();


}

void GameManager::trainInvisible() {

    GameEngine::spawnNewRandomAIControlledPlaneInARandomPlace(&params);
    GameEngine::spawnNewRandomAIControlledPlaneInARandomPlace(&params);

    GameEngine::init();
    GameEngine::setVisibility(false);
    GameEngine::setBeforeFrameFunction(
            GameEngine::checkPlanesCountAndSpawnNewPlaneAccordingly
    );

    GameEngine::setAfterFrameFunction(
            GameEngine::checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening
    );

    GameEngine::play();

}

void signalHandler(int signal) {

    int hours = GameEngine::totalGameTime / 60 / 60 / 60;
    GameEngine::totalGameTime%= (60*60*60);

    int minutes = GameEngine::totalGameTime / 60 / 60;
    GameEngine::totalGameTime%= (60*60);

    int seconds = GameEngine::totalGameTime / 60;

    std::cout << std::endl << "Simulation runned for " << hours << "h " << minutes << "m " << seconds << "s ";
    std::cout << std::endl << "In game-time" << std::endl;
    exit(0);

}

void GameManager::enableSignalCatching() {

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

}

void GameManager::trainVisibleContinue() {

    auto myPlane = new Plane(100, 100, 0);
    auto myController = new KeyboardController(myPlane);

    GameEngine::addObject(myPlane);
    GameEngine::addController(myController);



    //PLANE 1
    auto newPlane = new Plane(GameEngine::xPositionGenerator.generate(),
                              GameEngine::yPositionGenerator.generate(),
                              GameEngine::planeRotationGenerator.generate());

    auto newFOV = new FieldOfView(newPlane, VISUAL_CELLS_COUNT);

    auto newController = new NeuralController(&params, newPlane, newFOV);
    newController->loadFromFile(BEST_NETWORK_FILENAME);

    GameEngine::addObject(newPlane);
    GameEngine::addObject(newFOV);
    GameEngine::addController(newController);

    //PLANE 2
    auto newPlane2 = new Plane(GameEngine::xPositionGenerator.generate(),
                              GameEngine::yPositionGenerator.generate(),
                              GameEngine::planeRotationGenerator.generate());

    auto newFOV2 = new FieldOfView(newPlane2, VISUAL_CELLS_COUNT);

    auto newController2 = new NeuralController(&params, newPlane2, newFOV2);
    newController2->loadFromFile(BEST_NETWORK_FILENAME);

    GameEngine::addObject(newPlane2);
    GameEngine::addObject(newFOV2);
    GameEngine::addController(newController2);



    GameEngine::init();
    GameEngine::setVisibility(true);
    GameEngine::setBeforeFrameFunction(
            GameEngine::checkPlanesCountAndSpawnNewPlaneAccordingly
    );

    GameEngine::setAfterFrameFunction(
            GameEngine::checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening
    );

    GameEngine::play();

}

void GameManager::trainInvisibleContinue() {
    //PLANE 1
    auto newPlane = new Plane(GameEngine::xPositionGenerator.generate(),
                              GameEngine::yPositionGenerator.generate(),
                              GameEngine::planeRotationGenerator.generate());

    auto newFOV = new FieldOfView(newPlane, VISUAL_CELLS_COUNT);

    auto newController = new NeuralController(&params, newPlane, newFOV);
    newController->loadFromFile(BEST_NETWORK_FILENAME);

    GameEngine::addObject(newPlane);
    GameEngine::addObject(newFOV);
    GameEngine::addController(newController);

    //PLANE 2
    auto newPlane2 = new Plane(GameEngine::xPositionGenerator.generate(),
                               GameEngine::yPositionGenerator.generate(),
                               GameEngine::planeRotationGenerator.generate());

    auto newFOV2 = new FieldOfView(newPlane2, VISUAL_CELLS_COUNT);

    auto newController2 = new NeuralController(&params, newPlane2, newFOV2);
    newController2->loadFromFile(BEST_NETWORK_FILENAME);

    GameEngine::addObject(newPlane2);
    GameEngine::addObject(newFOV2);
    GameEngine::addController(newController2);



    GameEngine::init();
    GameEngine::setVisibility(false);
    GameEngine::setBeforeFrameFunction(
            GameEngine::checkPlanesCountAndSpawnNewPlaneAccordingly
    );

    GameEngine::setAfterFrameFunction(
            GameEngine::checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening
    );

    GameEngine::play();
}
