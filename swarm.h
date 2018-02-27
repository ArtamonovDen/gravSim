#pragma once

#include "particle.h"


class Swarm
{
public:
	const static int NPARTICLES = 5000;
	Swarm();
	virtual ~Swarm();

	const particle * const getParticles(){ return m_pParticles; }
private:
	particle *  m_pParticles;


};

