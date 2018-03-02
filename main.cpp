#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000


#define FRAME_TIME 1.0/60.0

#include <iostream>
#include "headers/Plane.h"


int main()
{


	sf::Time FrameTime = sf::seconds(FRAME_TIME);
	sf::Clock gameClock;   
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    

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
