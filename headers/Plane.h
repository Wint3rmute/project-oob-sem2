#include "headers/GameObject.h"

#define PLANE_SPEED 2
#define ACCELERATION_MULTIPLIER 0.03
#define MAX_SPEED 7
#define MIN_SPEED 1

#define DEG_2_RAD 0.0174532925
#define ROTATION_SPEED 1

enum DIRECTION {

	LEFT = -1,
	RIGHT = 1

};


class Plane : public GameObject {


	public:	
	float speed;
	sf::ConvexShape shape;
	
	public:
	Plane (int pos_x, int pos_y, float rotation);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void simulate ();
	
	void steer ();

	void turn (DIRECTION direction);

};