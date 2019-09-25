#include "particleGravityGenerator.hpp"

using namespace m_engine;

void ParticleGravityGenerator::updateForce(Particle& p, double time) {
	p.addForce(p.getInversMass() * gravity);
}
