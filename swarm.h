#pragma once

#include "particle.h"


class swarm
{
public:
	const static int NPARTICLES = 5000;
	swarm();
	virtual ~swarm();

	const particle * const getParticles(){ return m_pParticles; }
private:
	particle *  m_pParticles;


};

