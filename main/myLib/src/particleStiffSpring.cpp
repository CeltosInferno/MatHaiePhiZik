#include "particleStiffSpring.hpp"

using namespace m_engine;

void ParticleStiffSpring::updateForce(Particle& p, double time) {
	Vector3D f;
	double gamma = sqrt(4 * k - damping * damping) / 2;
	Vector3D c = damping / (2 * gamma) * p.getPos() + p.getVel() / gamma;

	f = (p.getPos() * cos(gamma * time) + c * sin(gamma * time)) * exp(-damping * time / 2);
	
	p.addForce(f);
}