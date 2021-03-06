//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/GameEngine.h"
#include "../headers/NeuralController.h"
#include "../headers/KeyboardController.h"

#include <iostream>
using namespace std;

// This makes the gameObjects vector visible in the file
std::vector <GameObject *> GameEngine :: gameObjects;
std::vector <GameObject *> GameEngine :: gameObjectsToRemove;
std::vector <Controller *> GameEngine :: controllers;
std::vector <Controller *> GameEngine :: controllersToRemove;
GameState GameEngine :: gameState;

int GameEngine :: matchClock;
unsigned long GameEngine :: totalGameTime;

sf::RenderWindow * GameEngine::window;
bool GameEngine :: graphicsEnabled;

/**
 * used for spawning new planes into the scene
 */
RandomGenerator GameEngine::xPositionGenerator(50, GAME_WINDOW_WIDTH - 50);
RandomGenerator GameEngine::yPositionGenerator(50, GAME_WINDOW_HEIGHT - 50);
RandomGenerator GameEngine::planeRotationGenerator(0, 360);


void GameEngine :: nothing() {
    /**
     * This function does nothing. That's it
     */

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
    }
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

    window = nullptr;

    matchClock = 0;
    totalGameTime = matchClock;

    gameState = IN_PROGRESS;
    sf::Time FrameTime = sf::seconds(FRAME_TIME);
    sf::Clock gameClock;

    if(graphicsEnabled)
    window = new sf::RenderWindow(
            sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
            "Hardcoded strings rock!");

    sf::Event event;

    while ( !graphicsEnabled ||
            (window->isOpen() && gameState == IN_PROGRESS))
    {

        if(graphicsEnabled)
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();


        }


        beforeFrame();


        simulate();

        if(graphicsEnabled)
            render(*window);

        clearRemoveQueue();


        afterFrame();

        if(graphicsEnabled)
            sf::sleep(FrameTime - gameClock.getElapsedTime());

        gameClock.restart();

        matchClock++;
    }

    GameEngine::printTotalGameTime();
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

/**
 * finds a plane inside gameObjects
 *
 * and makes a new one based on the weights of the old plane
 */
void GameEngine::spawnNewPlaneBasedOnTheDNAOfAnotherPlane() {

    for(auto object : gameObjects){
        if(object->objectType == PLANE){


            auto * plane = dynamic_cast<Plane *>(object);

            if (typeid(*plane->getController()) == typeid(KeyboardController)) {
                continue;
            }
            auto * controller = dynamic_cast<NeuralController *>(plane->getController());


            controller->saveToFile(BEST_NETWORK_FILENAME);

            if(plane == nullptr or controller == nullptr)
                cout << "Weird stuff that never should happen handled" << endl;

            auto newPlane = new Plane(xPositionGenerator.generate(),
                                      yPositionGenerator.generate(),
                                      planeRotationGenerator.generate());

            auto newFOV = new FieldOfView(newPlane, VISUAL_CELLS_COUNT);

            auto newController = new NeuralController(controller, newPlane, newFOV);
            newController->randomize(MUTATION_RATE) ;

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

    graphicsEnabled = true;
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

void GameEngine::simulate() {


    for (auto controller : controllers )
    {
        controller->control();
    }

    for (auto gameObject : gameObjects) {

        gameObject -> simulate();


        if(gameObject->collisionMode == AFFECTED) {

            for( auto possibleCollision : gameObjects)
            {
                if(possibleCollision->collisionMode == AFFECTOR and checkCollision(gameObject, possibleCollision)) {

                    auto * plane = dynamic_cast<Plane *>(gameObject);
                    auto * controller = plane->getController();

                    auto * fieldOfView = controller->fieldOfView;

                    if(fieldOfView != nullptr)
                        GameEngine::removeObject(fieldOfView);

                    GameEngine::removeController(controller);
                    GameEngine::removeObject(plane);
                    GameEngine::removeObject(possibleCollision);

                    cout << "SCORE" << endl;

                    totalGameTime+=matchClock;
                    matchClock = 0;
                }
            }
        }

    }


}

void GameEngine::render(sf::RenderWindow &window) {
    window.clear(BACKGROUND_COLOR);


    for (auto gameObject : gameObjects) {

        window.draw(*gameObject);
    }


    window.display();


}

void GameEngine::checkMatchTimeAndMutateRandomPlaneIfNothingIsHappening() {

    if(matchClock > TRAINING_MATCH_MAX_TIME) {

        cout << "Mutating planes due to lack of progress" << endl;
        mutateRandomPlane();
        totalGameTime+=matchClock;
        matchClock = 0;
    }

}

void GameEngine::mutateRandomPlane() {


    for (auto object : gameObjects) {
        if (object->objectType == PLANE) {


            auto *plane = dynamic_cast<Plane *>(object);
            auto *controller = dynamic_cast<NeuralController *>(plane->getController());

            controller->randomize(MUTATION_RATE);

        }
    }
}

void GameEngine::setVisibility(bool value) {
    graphicsEnabled = value;

}

void GameEngine::printTotalGameTime() {

    int hours = GameEngine::totalGameTime / 60 / 60 / 60;
    GameEngine::totalGameTime%= (60*60*60);

    int minutes = GameEngine::totalGameTime / 60 / 60;
    GameEngine::totalGameTime%= (60*60);

    int seconds = GameEngine::totalGameTime / 60;

    std::cout << std::endl << "Simulation runned for " << hours << "h " << minutes << "m " << seconds << "s ";
    std::cout << "in game-time" << std::endl;


}
