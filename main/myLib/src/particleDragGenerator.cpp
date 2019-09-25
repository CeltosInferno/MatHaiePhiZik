#include "particleDragGenerator.hpp"

using namespace m_engine;

void ParticleDragGenerator::updateForce(Particle& p, double time) {
	Vector3D vel = p.getVel();
	double velNorm = vel.norm();
	p.addForce(-vel.normalize()*(k1*velNorm + k2*velNorm*velNorm));
}
