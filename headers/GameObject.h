#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <SFML/Graphics.hpp>


class GameObject : public sf::Drawable {

public:
	bool wasRemoved = false;
	bool collisionsAffected = false;
	virtual void simulate() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
};

#endif