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
#include "RandomGenerator.h"
#include "Boost.h"
#include "../utils/structs.h"

enum GameState {
    IN_PROGRESS,
    DONE
};

class GameEngine {

    static sf::RenderWindow * window;
    static std::vector <GameObject *> gameObjectsToRemove;
    static std::vector <Controller *> controllers;
    static std::vector <Controller *> controllersToRemove;
    static GameState gameState;

    static void nothing();

    /*
     * This measures the ticks in the GameEngine
     *
     * this it NOT a normal clock
     */
    static int matchClock;
    static bool graphicsEnabled;


public:


    static unsigned long totalGameTime;

    inline static void (*beforeFrame)();
    inline static void (*afterFrame)();

    static void printTotalGameTime();

    static RandomGenerator xPositionGenerator;
    static RandomGenerator yPositionGenerator;
    static RandomGenerator planeRotationGenerator;

    static void setBeforeFrameFunction(void newBeforeFrame(void));
    static void setAfterFrameFunction(void newAfterFrame(void));
    static void resetBeforeAndAfterFrameFunctions();


    //TODO
    static std::vector <GameObject *> gameObjects;

    static void init();

    static void addObject(GameObject * newObject);
    static void addController(Controller * newController);
    static void removeController(Controller * controllerToRemove);

    static void removeObject (GameObject * objectToRemove);

    static void simulate();
    static void render(sf::RenderWindow & window);


    static void clearRemoveQueue();
    static void play();

    static double getDistance(GameObject * object1, GameObject * object2);
    static double getDistance(const sf::Vector2f&  object1, const sf::Vector2f& object2);

    static bool checkCollision(GameObject * object1, GameObject * object2);

    static void mutateRandomPlane();

    static void setVisibility(bool value);


    /*
     * This is where i keep my ridiculous function names
     */
    static void spawnNewPlaneBasedOnTheDNAOfAnotherPlane();
    static void checkPlanesCountAndSpawnNewPlaneAccordingly();
    static void spawnNewRandomAIControlledPlaneInARandomPlace(NetworkParams * params);
    static void checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening();


};

#endif //PROJECT_GAME_ENGINE_H
