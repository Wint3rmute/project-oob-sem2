#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class GameObject : public sf::Drawable {

	virtual void simulate() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    
	
};