#include "swarm.h"
#include "particle.h"

swarm::swarm()
{
	 m_pParticles = new particle[NPARTICLES];
}


swarm::~swarm()
{
	if( m_pParticles!=nullptr)
		delete [] m_pParticles;
}
