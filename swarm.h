#pragma once

#include "particle.h"


class Swarm
{
public:
	const static int NPARTICLES = 5000;
	Swarm();
	virtual ~Swarm();
	void update();

	const particle * const getParticles(){ return m_pParticles; }
private:
	particle *  m_pParticles;


};

