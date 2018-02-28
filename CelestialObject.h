#pragma once
#include <utility>
class CelestialObject
{
public:
	CelestialObject(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy) :
		weight(weight), radius(weight / 300 +2), x(x), y(y), ax(ax), ay(ay), vx(vx), vy(vy){}

	CelestialObject();

	~CelestialObject();
//private:
	unsigned long int weight;
	unsigned long int radius;	
	//std::pair<double, double> position;
	double x;
	double y;
	double ax, ay;
	double vx, vy;


};

