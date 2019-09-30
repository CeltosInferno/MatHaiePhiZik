#include "particleElasticString.hpp"

using namespace m_engine;

ParticleElasticString::ParticleElasticString(const Particle& ancrage, double K, double l0) :
	m_ancrage(&ancrage), m_K(K), m_l0(l0)
{}

void ParticleElasticString::updateForce(Particle& p, double time) {
	Vector3D delta = p.getPos() - m_ancrage->getPos();
	double l = delta.norm();
	if (l < m_l0) return; //no attraction, like a rope
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	p.addForce(force);
}
