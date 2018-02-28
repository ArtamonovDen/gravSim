#pragma once
#include <utility>
#include <stdlib.h>
#include <iostream>

#include <SDL.h>

class CelestialObject
{
public:
	CelestialObject(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy) :
		weight(weight), radius(weight / 300 +2), x(x), y(y), ax(ax), ay(ay), vx(vx), vy(vy){

		red = rand() % 255;
		green = rand() % 255;
		blue = rand() % 255;
		blue = 255;
	}

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
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

