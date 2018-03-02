#include "headers/GameObject.h"


#define BULLET_SPEED 5
#define BULLET_SIZE 3.f

#define DEG_2_RAD 0.0174532925


class Bullet : public GameObject {


	public:
	sf::CircleShape shape;
	float direction_x; // will be set only once, not per each frame.. so we save it globally
	float direction_y;

	public:
	Bullet (int pos_x, int pos_y, float rotation);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void simulate ();
	
};