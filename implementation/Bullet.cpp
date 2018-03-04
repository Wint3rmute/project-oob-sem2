#include "headers/Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>

Bullet :: Bullet (int pos_x, int pos_y, float rotation) : shape(BULLET_SIZE) {

	float direction = rotation * DEG_2_RAD;
	direction_x = cos(direction) * BULLET_SPEED;
	direction_y = sin(direction) * BULLET_SPEED;
	
}


void Bullet :: draw(sf::RenderTarget & target, sf::RenderStates states) const {

	target.draw(shape, states);

}

void Bullet :: simulate() {

	if (
		shape.getPosition().x > GAME_WINDOW_WIDTH ||
		shape.getPosition().x < 0 ||
		shape.getPosition().y > GAME_WINDOW_HEIGHT ||
		shape.getPosition().y < 0
		) {
		GameEngine::removeObject(this);
		//delete this;
		return;
	}

	shape.move(direction_x, direction_y);

}

Bullet :: ~Bullet() {
	std::cout << "removed!" << std::endl;
}