#include "particleLink.hpp"

using namespace m_engine;

ParticleLink::ParticleLink(Particle* pa, Particle* pb)
{
	particles[0] = pa;
	particles[1] = pb;
}

double ParticleLink::currentLength() const {
	return (particles[0]->getPos() - particles[1]->getPos()).norm();
}

void ParticleLink::addContact() {
	//Particle* pa = particles[0];
	//Particle* pb = particles[1];
	//double dist = pa->getPos().distance(pb->getPos());
	//ajouter le resultat
}