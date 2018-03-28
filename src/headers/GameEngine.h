//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_GAME_ENGINE_H
#define PROJECT_GAME_ENGINE_H


#include <vector>
#include <cmath>
#include "GameObject.h"
#include "Controller.h"
#include "Bullet.h"

enum GameState {
    IN_PROGRESS,
    DONE
};

class GameEngine {
    
    static std::vector <GameObject *> gameObjects;
    static std::vector <GameObject *> gameObjectsToRemove;
    static std::vector <Controller *> controllers;
    static std::vector <Controller *> controllersToRemove;
    static GameState gameState;

public:

    static void addObject(GameObject * newObject);
    static void addController(Controller * newController);
    static void removeController(Controller * controllerToRemove);

    static void removeObject (GameObject * objectToRemove);
    static void simulateAndRender (sf::RenderWindow & window);
    static void clearRemoveQueue();
    static void play();

    static double getDistance(GameObject * object1, GameObject * object2);
    static bool checkColision(GameObject * object1, GameObject * object2);


};

#endif //PROJECT_GAME_ENGINE_H
