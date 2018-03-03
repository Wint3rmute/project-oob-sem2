#include "utils/constants.h"
#include "headers/Plane.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>

#define TELEPORTATION_TRIGGER_OFFSET 20

using namespace std;


Plane::Plane (int pos_x, int pos_y, float rotation) {

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


void Plane :: draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(shape, states);
	
}

void Plane :: simulate() {


	float angle_rad = shape.getRotation() * DEG_2_RAD;

	shape.move(cos(angle_rad) * speed , sin(angle_rad) * speed);

	speed += sin(angle_rad) * ACCELERATION_MULTIPLIER;

	if ( shape.getPosition().y <= -TELEPORTATION_TRIGGER_OFFSET)
		shape.move(0, GAME_WINDOW_HEIGHT + TELEPORTATION_TRIGGER_OFFSET);

	if ( shape.getPosition().y >= GAME_WINDOW_HEIGHT + TELEPORTATION_TRIGGER_OFFSET)
		shape.move(0, -GAME_WINDOW_HEIGHT - TELEPORTATION_TRIGGER_OFFSET);
	
	if ( shape.getPosition().x <= -TELEPORTATION_TRIGGER_OFFSET )
	 	shape.move(GAME_WINDOW_WIDTH + TELEPORTATION_TRIGGER_OFFSET,0);	

	if ( shape.getPosition().x >= GAME_WINDOW_WIDTH + TELEPORTATION_TRIGGER_OFFSET)
		shape.move(-GAME_WINDOW_WIDTH - TELEPORTATION_TRIGGER_OFFSET, 0) ;


	if (speed > MAX_SPEED)
		speed = MAX_SPEED;

	else if (speed < MIN_SPEED)
		speed = MIN_SPEED;


	//std::cout << speed << std::endl;
	steer();

}

void Plane :: steer() {

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left)) 
    	turn(LEFT);

	else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
		turn(RIGHT);

}

void Plane :: turn(DIRECTION direction) {

	shape.rotate(direction * ROTATION_SPEED * speed);

}
