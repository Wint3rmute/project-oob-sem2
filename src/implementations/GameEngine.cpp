//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/GameEngine.h"
#include "../headers/GameObject.h"
#include "../utils/constants.h"

#include <iostream>
using namespace std;

// This makes the gameObjects vector visible in the file
std::vector <GameObject *> GameEngine :: gameObjects;
std::vector <GameObject *> GameEngine :: gameObjectsToRemove;
std::vector <Controller *> GameEngine :: controllers;


void GameEngine :: addObject (GameObject * newObject) {

    gameObjects.push_back(newObject);

}

void GameEngine :: removeObject (GameObject * objectToRemove) {

    if(objectToRemove->wasRemoved)
        return;

    gameObjectsToRemove.push_back(objectToRemove);

    //delete objectToRemove;
    gameObjects.erase(
            std::remove(
                    gameObjects.begin(),
                    gameObjects.end(),
                    objectToRemove),
            gameObjects.end());

    objectToRemove->wasRemoved = true;


}


void GameEngine :: simulateAndRender (sf::RenderWindow & window) {

    window.clear();

    for (auto controller : controllers )
    {
        controller->control();
    }

    for (auto gameObject : gameObjects) {

        gameObject -> simulate();
        window.draw(*gameObject);

    }

    window.display();

}

void GameEngine :: clearRemoveQueue () {

    while (not gameObjectsToRemove.empty()) {
        delete gameObjectsToRemove.back();
        gameObjectsToRemove.pop_back();
    }


}

void GameEngine :: play() {

    sf::Time FrameTime = sf::seconds(FRAME_TIME);
    sf::Clock gameClock;

    sf::RenderWindow window(
            sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
            "Hardcoded strings rock!");


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        simulateAndRender(window);
        clearRemoveQueue();
        sf::sleep(FrameTime - gameClock.getElapsedTime());
        gameClock.restart();

    }

}

void GameEngine::addController(Controller *newController) {
    controllers.push_back(newController);
}


double GameEngine::getDistance(GameObject * object1, GameObject * object2) {

    double deltaX = object1->getPosition().x - object2->getPosition().x;
    double deltaY = object1->getPosition().y - object2->getPosition().y;

    return sqrt( pow( deltaX, 2 ) + pow( deltaY, 2 ) );
}

bool GameEngine::checkColision(GameObject *object1, GameObject *object2) {
    return getDistance(object1, object2) < object1->size + object2->size;
}
