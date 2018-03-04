#include "utils/constants.h"
#include "headers/GameObject.h"
#include <vector>

class GameEngine{

	static std::vector <GameObject *> gameObjects;

public:

	static void addObject(GameObject * newObject);
	static void removeObject (GameObject * objectToRemove);
	static void simulateAndRender (sf::RenderWindow & window);
	static void play();

};