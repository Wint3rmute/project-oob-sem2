#pragma once
#include <SFML/Graphics.hpp>


class GameObject : public sf::Drawable {

	bool collisionsAffected = false;

	virtual void simulate() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
};