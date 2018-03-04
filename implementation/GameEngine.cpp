#include "headers/GameEngine.h"

#include <iostream>
using namespace std;


void GameEngine :: addObject (GameObject * newObject) {

	gameObjects.push_back(newObject);

}

void GameEngine :: removeObject (GameObject * objectToRemove) {

	gameObjects.erase(
		std::remove(
			gameObjects.begin(),
			gameObjects.end(),
			objectToRemove),
		gameObjects.end());

	delete objectToRemove;
}


void GameEngine :: simulateAndRender (sf::RenderWindow & window) {

	window.clear();

	for (auto gameObject : gameObjects) {

		gameObject -> simulate();
		window.draw(*gameObject);
		std::cout << "done" << std::endl;
	
	}

	window.display();

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

    	

        this -> simulateAndRender(window);
	


        

        sf::sleep(FrameTime - gameClock.getElapsedTime());
        gameClock.restart();
    }

}