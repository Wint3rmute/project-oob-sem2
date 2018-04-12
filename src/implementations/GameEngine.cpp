//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/GameEngine.h"
#include "../headers/NeuralController.h"

#include <iostream>
using namespace std;

// This makes the gameObjects vector visible in the file
std::vector <GameObject *> GameEngine :: gameObjects;
std::vector <GameObject *> GameEngine :: gameObjectsToRemove;
std::vector <Controller *> GameEngine :: controllers;
std::vector <Controller *> GameEngine :: controllersToRemove;
GameState GameEngine :: gameState;



RandomGenerator GameEngine::xPositionGenerator(50, GAME_WINDOW_WIDTH - 50);
RandomGenerator GameEngine::yPositionGenerator(50, GAME_WINDOW_HEIGHT - 50);
RandomGenerator GameEngine::planeRotationGenerator(0, 360);


void GameEngine :: nothing() {
    /*
     * This function does nothing. That's it
     */


    //cout << "i do nothing" << endl;
}

void GameEngine :: addObject (GameObject * newObject) {

    gameObjects.push_back(newObject);

}

void GameEngine::removeController(Controller *controllerToRemove) {

    if(controllerToRemove == nullptr) //THE ULTIMATE SANITY CHECK
        return;

    if(controllerToRemove->wasRemoved)
        return;

    controllersToRemove.push_back(controllerToRemove);

    controllers.erase(
            std::remove(
                    controllers.begin(),
                    controllers.end(),
                    controllerToRemove),
            controllers.end());

    controllerToRemove->wasRemoved = true;

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

void GameEngine :: checkPlanesCountAndSpawnNewPlaneAccordingly() {

    if(Plane::howManyPlanesAreThere() < HOW_MANY_PLANES_ON_MAP_WHILE_TRAINING) {
        spawnNewPlaneBasedOnTheDNAOfAnotherPlane();

        for(auto gameObject : GameEngine::gameObjects) {
            if(gameObject->objectType == BULLET)
                GameEngine::removeObject(gameObject);
        }

        GameEngine::clearRemoveQueue();
        //cout << "DONE" << endl;
    }
}


void GameEngine :: simulateAndRender (sf::RenderWindow & window) {


    window.clear(BACKGROUND_COLOR);

    for (auto controller : controllers )
    {
        controller->control();
    }

    for (auto gameObject : gameObjects) {

        gameObject -> simulate();
        window.draw(*gameObject);


        if(gameObject->collisionMode == AFFECTED) {

            for( auto possibleCollision : gameObjects)
            {
                if(possibleCollision->collisionMode == AFFECTOR and checkCollision(gameObject, possibleCollision)) {

                    auto * plane = dynamic_cast<Plane *>(gameObject);
                    auto * controller = dynamic_cast<NeuralController *>(plane->getController());
                    auto * fieldOfView = controller->fieldOfView;


                    GameEngine::removeObject(fieldOfView);
                    GameEngine::removeController(controller);
                    GameEngine::removeObject(plane);
                    GameEngine::removeObject(possibleCollision);
                }
            }
        }

    }

    window.display();

}

void GameEngine :: clearRemoveQueue () {

    while (not gameObjectsToRemove.empty()) {
        delete gameObjectsToRemove.back();
        gameObjectsToRemove.pop_back();
    }

    while(not controllersToRemove.empty()) {
        delete controllersToRemove.back();
        controllersToRemove.pop_back();
    }

}

void GameEngine :: play() {

    gameState = IN_PROGRESS;
    sf::Time FrameTime = sf::seconds(FRAME_TIME);
    sf::Clock gameClock;

    sf::RenderWindow window(
            sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
            "Hardcoded strings rock!");


    while (window.isOpen() && gameState == IN_PROGRESS)
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                cout << GameEngine::gameObjects.size() << endl;
            }
        }

        beforeFrame();

        simulateAndRender(window);
        clearRemoveQueue();

        afterFrame();

        sf::sleep(FrameTime - gameClock.getElapsedTime());
        gameClock.restart();

    }

}

void GameEngine::addController(Controller *newController) {
    controllers.push_back(newController);
}


double GameEngine::getDistance(GameObject * object1, GameObject * object2) {

    return getDistance(object1->getPosition(), object2->getPosition());
 }

double GameEngine::getDistance(const sf::Vector2f&  object1, const sf::Vector2f& object2) {

    double deltaX = object1.x - object2.x;
    double deltaY = object1.y - object2.y;

    return sqrt( pow( deltaX, 2 ) + pow( deltaY, 2 ) );
}

bool GameEngine::checkCollision(GameObject *object1, GameObject *object2) {
    return getDistance(object1, object2) < object1->size + object2->size;
}

void GameEngine::spawnNewPlaneBasedOnTheDNAOfAnotherPlane() {

    for(auto object : gameObjects){
        if(object->objectType == PLANE){


            auto * plane = dynamic_cast<Plane *>(object);
            auto * controller = dynamic_cast<NeuralController *>(plane->getController());


            controller->saveToArchive();
            controller->saveToFile("last_best.network");

            if(plane == nullptr or controller == nullptr)
                cout << "Weird stuff that never should happen handled" << endl;

            auto newPlane = new Plane(xPositionGenerator.generate(),
                                      yPositionGenerator.generate(),
                                      planeRotationGenerator.generate());

            auto newFOV = new FieldOfView(newPlane, VISUAL_CELLS_COUNT);

            auto newController = new NeuralController(controller, newPlane, newFOV);
            newController->randomize(0.1);

            GameEngine::addObject(newPlane);
            GameEngine::addObject(newFOV);

            GameEngine::addController(newController);
            return;

        }
    }

}

void GameEngine::setBeforeFrameFunction(void (*newBeforeFrame)(void)) {

    beforeFrame = newBeforeFrame;
}

void GameEngine::setAfterFrameFunction(void (*newAfterFrame)(void)) {

    afterFrame = newAfterFrame;
}

void GameEngine::resetBeforeAndAfterFrameFunctions() {

    beforeFrame = GameEngine::nothing;
    afterFrame = GameEngine::nothing;


}

void GameEngine::init() {
    resetBeforeAndAfterFrameFunctions();

}

void GameEngine::spawnNewRandomAIControlledPlaneInARandomPlace(NetworkParams * params) {

    auto newPlane = new Plane(xPositionGenerator.generate(),
                              yPositionGenerator.generate(),
                              planeRotationGenerator.generate());

    auto newFOV = new FieldOfView(newPlane, VISUAL_CELLS_COUNT);

    auto newController = new NeuralController(params, newPlane, newFOV);

    GameEngine::addObject(newPlane);
    GameEngine::addObject(newFOV);

    GameEngine::addController(newController);

}
