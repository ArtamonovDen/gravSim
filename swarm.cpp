#include "swarm.h"
#include "particle.h"

Swarm::Swarm()
{
	 m_pParticles = new particle[NPARTICLES];
}


Swarm::~Swarm()
{
	if( m_pParticles!=nullptr)
		delete [] m_pParticles;
}
