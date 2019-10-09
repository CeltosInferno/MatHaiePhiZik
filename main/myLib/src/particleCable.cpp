#include "particleCable.hpp"

using namespace m_engine;

ParticleCable::ParticleCable(Particle* pa, Particle* pb, double length, double restitution):
	ParticleLink(pa, pb), m_length(length), m_restitution(restitution)
{

}

void ParticleCable::addContact() {
	//TODO
}