#include "particle.h"
#include <stdlib.h>
#include <time.h>

particle::particle()

{
	m_x = ((2.0 *rand()) / RAND_MAX) - 1;
	m_y = ((2.0 *rand()) / RAND_MAX) - 1;
	

}


particle::~particle()
{
}

void particle::update(){
	const double speed = 0.01;
	m_x += speed;
	m_y += speed;

}