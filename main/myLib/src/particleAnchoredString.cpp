#include "particleAnchoredString.hpp"

using namespace m_engine;

ParticleAnchoredString::ParticleAnchoredString(const Vector3D& ancrage, double K, double l0): 
	m_ancrage(ancrage), m_K(K), m_l0(l0)
{}

void ParticleAnchoredString::updateForce(Particle& p, double time) {
	Vector3D delta = p.getPos() - m_ancrage;
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	p.addForce(force);
}

