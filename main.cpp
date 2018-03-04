#include "utils/constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#include <iostream>
#include "headers/Plane.h"
#include "headers/GameEngine.h"


int main()
{

   
	GameEngine engine;
   	Plane *plane = new Plane(50, 50, 90);

   	engine.addObject(plane);
   	engine.play();
   
    return 0;
}
