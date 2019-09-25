#include "particleString.hpp"

using namespace m_engine;

ParticleString::ParticleString(const Particle& ancrage, double K, double l0) :
	m_ancrage(&ancrage), m_K(K), m_l0(l0)
{}

void ParticleString::updateForce(Particle& p, double time) {
	Vector3D delta = p.getPos() - m_ancrage->getPos();
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	p.addForce(force);
}
