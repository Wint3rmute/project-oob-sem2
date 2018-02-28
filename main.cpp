#include <SFML/Graphics.hpp>
#include <math.h>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1000

#define PLANE_SPEED 0.05


#define DEG_2_RAD 0.0174532925
#define ROTATION_SPEED 0.03



class Plane : public sf::Drawable
{

	public:	
	float speed;
	sf::ConvexShape shape;
	
	public:
	Plane(int pos_x, int pos_y, float rotation)
	{
		speed = PLANE_SPEED;

		// resize shape to 5 points
		shape.setPointCount(5);

		// define the shape points
		shape.setPoint(0, sf::Vector2f(0, 0));
		shape.setPoint(1, sf::Vector2f(30, 0));
		shape.setPoint(2, sf::Vector2f(50, 10));
		shape.setPoint(3, sf::Vector2f(30, 20));
		shape.setPoint(4, sf::Vector2f(0, 20));
	
	
		shape.setPosition(pos_x, pos_y);
		shape.setRotation(rotation);	
	
	}


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    	{
        	target.draw(shape, states);
	}
	
	void simulate()
	{
		float angle_rad = shape.getRotation() * DEG_2_RAD;
		shape.move(cos(angle_rad) * PLANE_SPEED , sin(angle_rad) * PLANE_SPEED);
		speed+=cos(angle_rad) * 10;
		steer();
	
	}
	
	void steer()
	{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{	
		    	// left key is pressed: move our character
			shape.rotate(-ROTATION_SPEED);
		
		}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{

			shape.rotate(ROTATION_SPEED);
		}	
	
	}
};

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    

    Plane plane(50, 50, 90);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	
	
    	plane.simulate();
	
        window.clear();
        window.draw(plane);
        window.display();
    }

    return 0;
}
