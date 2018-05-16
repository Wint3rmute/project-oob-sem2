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

/**
 * The main game engine,
 *
 * Controls the flow of the game
 */
class GameEngine {

    static sf::RenderWindow * window;
    static std::vector <GameObject *> gameObjectsToRemove;
    static std::vector <Controller *> controllers;
    static std::vector <Controller *> controllersToRemove;
    static GameState gameState;

    static void nothing();

    /**
     * This measures the ticks in the GameEngine
     *
     * this it NOT a normal clock
     */
    static int matchClock;
    static bool graphicsEnabled;


public:


    static unsigned long totalGameTime;

    /**
     * functions that can be runned by the GameEngine
     * before or after each simulation frame
     */
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

    /**
     * functions for adding objects and controllers to the scene
     */
    static void addObject(GameObject * newObject);
    static void addController(Controller * newController);

    /**
     * functions for removing objects and controllers from the scene
     */
    static void removeController(Controller * controllerToRemove);
    static void removeObject (GameObject * objectToRemove);

    /**
     * functions for simulating and rendering a simgle frame
     */
    static void simulate();
    static void render(sf::RenderWindow & window);


    /**
     * if true - window is shown
     *
     * if false - game goes on 100x faster than normally,
     * used for faster training
     *
     * needs to be set BEFORE GameEngine::play()
     */
    static void setVisibility(bool value);

    /**
     * a helper for object removing
     */
    static void clearRemoveQueue();


    /**
     * this function starts the GameEngine after everything was loaded into the scene
     */
    static void play();

    /**
     * helper functions for collision detection
     */
    static double getDistance(GameObject * object1, GameObject * object2);
    static double getDistance(const sf::Vector2f&  object1, const sf::Vector2f& object2);
    static bool checkCollision(GameObject * object1, GameObject * object2);

    /**
     * This function is used when nothing happens at the game scene for a long time,
     * prevents endless loops of planes doing nothing
     */
    static void mutateRandomPlane();



    /**
     * Ridiculous function names
     *
     * Their names are very self-explanatory
     */
    static void spawnNewPlaneBasedOnTheDNAOfAnotherPlane();
    static void checkPlanesCountAndSpawnNewPlaneAccordingly();
    static void spawnNewRandomAIControlledPlaneInARandomPlace(NetworkParams * params);
    static void checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening();


};

#endif //PROJECT_GAME_ENGINE_H
