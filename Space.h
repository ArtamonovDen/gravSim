#pragma once
#include "CelestialObject.h"

#include <vector>
class Space
{
public:
	//double scale; //thousand km per 1px
	Space();
	~Space();

	void add(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy);

	double getDistance(CelestialObject*, CelestialObject*);
	bool is_collapse(CelestialObject*, CelestialObject*, double);

	void somethingHappening();

	void udpateObject(CelestialObject*, double, double,double, int , int);

private:
	std::vector<CelestialObject*> objects;
	const double G = 0.005; //Grav. constant
	const double dt = 0.005; //short time period for computing integrals
};

