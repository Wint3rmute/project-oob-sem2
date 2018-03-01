#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000

#define PLANE_SPEED 2
#define ACCELERATION_MULTIPLIER 0.03
#define MAX_SPEED 7
#define MIN_SPEED 1

#define DEG_2_RAD 0.0174532925
#define ROTATION_SPEED 1

#define FRAME_TIME 1.0/60.0

#include <iostream>
#include "headers/GameEngine.h"

enum DIRECTION {
	LEFT = -1,
	RIGHT = 1
};

class Plane : public sf::Drawable {

	public:	
	float speed;
	sf::ConvexShape shape;
	
	public:
	Plane (int pos_x, int pos_y, float rotation) {
		speed = PLANE_SPEED;

		// resize shape to 5 points
		shape.setPointCount(5);

		// define the shape points
		shape.setPoint(0, sf::Vector2f(0, 0));
		shape.setPoint(1, sf::Vector2f(30, 0));
		shape.setPoint(2, sf::Vector2f(50, 7));
		shape.setPoint(3, sf::Vector2f(30, 14));
		shape.setPoint(4, sf::Vector2f(0, 14));
	
	
		shape.setPosition(pos_x, pos_y);
		shape.setRotation(rotation);	
		shape.setOrigin(25,10);
	}


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        	target.draw(shape, states);
	}
	
	void simulate () {

		float angle_rad = shape.getRotation() * DEG_2_RAD;
		shape.move(cos(angle_rad) * speed , sin(angle_rad) * speed);
		speed+=sin(angle_rad) * ACCELERATION_MULTIPLIER;

		if (speed > MAX_SPEED)
			speed = MAX_SPEED;
		else if (speed < MIN_SPEED)
			speed = MIN_SPEED;

		std::cout << speed << std::endl;
		steer();
	
	}
	
	void steer () {
	
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left)) {	
	    	turn(LEFT);
		
		} else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right)) {

			turn(RIGHT);
		}	
	
	}

	void turn (DIRECTION direction) {

		shape.rotate(direction * ROTATION_SPEED * speed);
	}
};

int main()
{
	GameEngine game;
	game.pole();
	game.pole();
	game.lyse();
	game.pole();


	return 0;
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
