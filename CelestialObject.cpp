#include "CelestialObject.h"

#include <iostream>

CelestialObject::CelestialObject(){


  /*  weight = rand() % 100000;
	radius = rand() % 10;*/
	//weight = rand() % 1000 + 300;
	weight = 400;

	std::cout << weight << std::endl;
	radius = weight / 300+2;
	//std::pair<double, double> position;
     x = ((2.0 *rand()) / RAND_MAX) - 1;
	 y = ((2.0 *rand()) / RAND_MAX) - 1;;
	ax = 0;
	ay = 0;

	/*vx = 0;
	vy = 0;*/
	vx = 0;
	vy = 0;
}

CelestialObject::~CelestialObject()
{
}
