#include "utils/constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#include <iostream>
#include "headers/Plane.h"


int main()
{

   sf::Time FrameTime = sf::seconds(FRAME_TIME);
	sf::Clock gameClock;   
    sf::RenderWindow window(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "SFML works!");
    

    Plane plane(50, 50, 90);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	
	
    	plane.simulate();
	
        window.clear();
        window.draw(plane);
        window.display();

        sf::sleep(FrameTime - gameClock.getElapsedTime());
        gameClock.restart();
    }

    return 0;
}
