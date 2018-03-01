#pragma once
#include "CelestialObject.h"
#include "Screen.h"

#include <vector>
class Space
{
public:
	//double scale; //thousand km per 1px
	Space();
	~Space();

	void add(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy);
	void add(int N);//Add N random-pos objects
	void addObj(CelestialObject*A){ objects.push_back(A); }


	double getDistance(CelestialObject*, CelestialObject*);
	bool is_collapse(CelestialObject*, CelestialObject*, double);

	void somethingHappening();

	void udpateObject(CelestialObject*);
	void createByButton(unsigned long int weight, int x, int y, double ax, double ay, double vx, double vy);

	void loop();
	void merge(CelestialObject*, CelestialObject*);
	

	Screen spaceScreen;

private:
	std::vector<CelestialObject*> objects;
	const double G = 0.8; //Grav. constant
	const double dt = 0.05; //short time period for computing integrals
};

