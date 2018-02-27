#include "CelestialObject.h"


CelestialObject::CelestialObject(){


  /*  weight = rand() % 100000;
	radius = rand() % 10;*/
	weight = 10000;
	radius = 5;
	//std::pair<double, double> position;
     x = ((2.0 *rand()) / RAND_MAX) - 1;
	 y = ((2.0 *rand()) / RAND_MAX) - 1;;
	ax = 0;
	ay = 0;

	vx = 0;
	vy = 0;
}

CelestialObject::~CelestialObject()
{
}
