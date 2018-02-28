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
void Swarm::update(){
	for (int i = 0; i < Swarm::NPARTICLES; i++){
		m_pParticles[i].update();

	}
}