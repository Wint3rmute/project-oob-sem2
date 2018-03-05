#ifndef BULLET_H
#define BULLET_H
#include "utils/constants.h"
#include "headers/GameObject.h"
#include "headers/GameEngine.h"


class Bullet : public GameObject {


	public:
	sf::CircleShape shape;
	float direction_x; // will be set only once, not per each frame.. so we save it globally
	float direction_y;

	public:
	Bullet (int pos_x, int pos_y, float rotation);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void simulate ();

	~Bullet();
};

#endif