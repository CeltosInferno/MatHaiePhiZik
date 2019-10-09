#include "particleRod.hpp"

using namespace m_engine;

ParticleRod::ParticleRod(Particle* pa, Particle* pb, double length):
	ParticleLink(pa, pb), m_length(length)
{

}

void ParticleRod::addContact() {
	//TODO
}