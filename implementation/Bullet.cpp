#include "headers/Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

Bullet::Bullet (int pos_x, int pos_y, float rotation) : shape(BULLET_SIZE) {

		float direction = rotation * DEG_2_RAD;
		direction_x = cos(direction) * BULLET_SPEED;
		direction_y = sin(direction) * BULLET_SPEED;
	
}


void Bullet :: draw(sf::RenderTarget& target, sf::RenderStates states) const {
    	target.draw(shape, states);
}

void Bullet :: simulate() {

		shape.move(direction_x, direction_y);

	
}