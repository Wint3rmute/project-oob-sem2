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
/**
 * @file GameEngine.h
 * File contains GameEngine class declaration and GameState enum definition
 */

/**
 * @enum GameState
 * Phases that game can be in
 */
enum GameState {
    IN_PROGRESS,
    DONE
};

/**
 *
 * @brief The main game engine,
 *
 * Controls the flow of the game, checks collisions, handles events,
 * manages planes, simulates all objects, has function to add objects to game and remove them from it.
 *
 * Also manages time flow in app.
 */
class GameEngine {
    /**
    * Game window variable
    */
    static sf::RenderWindow * window;
    /**
     * Resizing vector with all game objects to remove in this frame
     */
    static std::vector <GameObject *> gameObjectsToRemove;
    /**
     * Vector with all Controller instances currently in game
     */
    static std::vector <Controller *> controllers;
    /**
     * Vector with all Controller instances to remove in this frame
     */
    static std::vector <Controller *> controllersToRemove;
    /**
     * State of the game @see GameState
     */
    static GameStat gameState;
    /**
     * @brief it's really nothing
     * Nothing
     */
    static void nothing();

    /**
     * This measures the ticks in the GameEngine
     */
    static int matchClock;
    /**
     * Variable that indicates if app runs with graphics
     */
    static bool graphicsEnabled;


public:

    /**
     * Game time in sec
     */
    static unsigned long totalGameTime;

    /**
     * @brief Before frame function
     * Function that can be run before each rendered frame
     */
    inline static void (*beforeFrame)();
    /**
     * @brief After frame function
     * Function that can be run after each rendered frame
     */
    inline static void (*afterFrame)();
    /**
     * @brief Prints total game time
     * Prints current game time that passed in game on standard output.
     * @note It's time that passed in simulation, not time that passed in reality
     */
    static void printTotalGameTime();
    /**
     * @name Random coordinates generator
     * Functions that generate random object coordinates and rotation
     * @{
     */
    static RandomGenerator xPositionGenerator;
    static RandomGenerator yPositionGenerator;
    static RandomGenerator planeRotationGenerator;
    /** @}*/
    /**
     * @brief setter of beforeFrame function
     * Sets new function that will be toggled before each frame
     * @param newBeforeFrame void function with no parameters
     */
    static void setBeforeFrameFunction(void newBeforeFrame(void));
    /**
     * @brief setter of afterFrame function
     * Sets new function that will be toggled after each frame
     * @param newAfterFrame void function with no parameters
     */
    static void setAfterFrameFunction(void newAfterFrame(void));
    /**
     * @brief Resets both before and after frame functions
     * Sets both functions to GameEngine::nothing()
     */
    static void resetBeforeAndAfterFrameFunctions();


    /**
     * Vector with all objects currently in the game
     */
    static std::vector <GameObject *> gameObjects;

    /**
     * @brief Initializes game engine with graphics
     * Initializes game engine with graphics and also sets both before and after frame functions to nothing
     */
    static void init();

    /**
     * @brief Adds GameObject to game
     * Function for adding every GameObject to the scene
     * @param newObject GameObject that needs to be added
     */
    static void addObject(GameObject * newObject);
    /**
     * @brief Adds Controllers to game
     * Function for adding every Controller to the scene
     * @param newController Controller that needs to be added
     */
    static void addController(Controller * newController);

    /**
     * @brief Removes Controller from game
     * Function for removing Controller from the game
     * @param controllerToRemove Controller that needs to be removed
     */
    static void removeController(Controller * controllerToRemove);
    /**
     * @brief Removes GameObject from game
     * Function for removing GameObject from the game
     * @param objectToRemove GameObject that needs to be removed
     */
    static void removeObject (GameObject * objectToRemove);

    /**
     * @brief World simulating function
     * Simulates behaviour of window content, updates state of objects
     */
    static void simulate();
    /**
     * @brief SFML rendering
     * SFML function that randers current frame
     * @param window Game window
     */
    static void render(sf::RenderWindow & window);



    /**
    * @brief Setting if program is visible
     * Function sets window visibility
    * @param value If true - window is visible; else not, but game runs 100x faster
     * @note Needs to be set BEFORE play() function
    */
    static void setVisibility(bool value);

    /**
     * @brief Object removing assisting function
     * Helper function for removing GameObjects, used to prevent segfaults.
     */
    static void clearRemoveQueue();


    /**
     * @brief Starts game engine
     * This function starts the GameEngine after everything was loaded into the scene
     */
    static void play();

    /**
     * @brief Measures distance between two objects
     * Helper collision function that measures distance between 2 game objects
     * @param object1 First object
     * @param object2 Second object
     * @return Distance between object 1 and 2
     */
    static double getDistance(GameObject * object1, GameObject * object2);
    static double getDistance(const sf::Vector2f&  object1, const sf::Vector2f& object2);
    /**
     * @brief Checks collision between 2 given objects
     * Checks if collision occurred between 2 GameObjects. It's based on checking size and calculating distance between
     * those objects.
     * @param object1 First object
     * @param object2 Second object
     * @return true if objects are colliding, false if not
     */
    static bool checkCollision(GameObject * object1, GameObject * object2);

    /**
     * @brief Replaces one random plane in game
     * This function is used when nothing happens at the game scene for a long time,
     * prevents endless loops of planes doing nothing
     */
    static void mutateRandomPlane();
    /**
     * @brief Spawns plane with new neural network
     * Spawns new plane based on the DNA of another plane with mutated neural network values.
     */
    static void spawnNewPlaneBasedOnTheDNAOfAnotherPlane();
    /**
     * @brief Spawns new plane if planes are missing
     * Checks if current plane number is equal to set value and spawns adequate number of them to reduce differences.
     */
    static void checkPlanesCountAndSpawnNewPlaneAccordingly();
    /**
     * @brief Spawns AI controlled plane in a random place
     * Spawns AI controlled plane in a random place with neural network arguments passed as a parameter
     * @param params NetworkParams for AI bot neural network
     */
    static void spawnNewRandomAIControlledPlaneInARandomPlace(NetworkParams * params);
    /**
     * @brief Checks if game runs for too long without plane destroyed
     * If planes don't shoot themselves for a set period of time this function detects it and calls mutateRandomPlane() function
     */
    static void checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening();


};

#endif //PROJECT_GAME_ENGINE_H

