#include "constants.h"
#include "headers/GameObject.h"


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