#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "utils/constants.h"
#include "headers/GameObject.h"
#include <vector>

class GameEngine{

	static std::vector <GameObject *> gameObjects;
	static std::vector <GameObject *> gameObjectsToRemove;

public:

	static void addObject(GameObject * newObject);
	static void removeObject (GameObject * objectToRemove);
	static void simulateAndRender (sf::RenderWindow & window);
	static void clearRemoveQueue();
	static void play();

};

#endif