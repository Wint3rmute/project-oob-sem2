#include "utils/constants.h"
#include "headers/GameObject.h"
#include <vector>

class GameEngine{

	std::vector <GameObject *> gameObjects;

public:

	void addObject(GameObject * newObject);
	void removeObject (GameObject * objectToRemove);
	void simulateAndRender (sf::RenderWindow & window);
	void play();

};