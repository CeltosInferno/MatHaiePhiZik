#include "forceRegister.hpp"
#include <algorithm>

using namespace m_engine;

void ForceRegister::add(Particle* p, ParticleForceGenerator* Fg) {
	ForceStoredParticle fs = { p, Fg };
	m_Preg.push_back(fs);
}

void ForceRegister::add(RigidBody* r, RigidBodyForceGenerator* frg) {
	ForceStoredRigidBody fs = { r, frg };
	m_Rreg.push_back(fs);
}

void ForceRegister::applyForces(double time) {
	for (ForceStoredParticle fs : m_Preg) {
		fs.Fg->updateForce(*(fs.p), time);
	}
	for (ForceStoredRigidBody fs : m_Rreg) {
		fs.Frg->updateForce(*(fs.r), time);
	}
}

void ForceRegister::remove(Particle* p, ParticleForceGenerator* Fg) {
	ForceStoredParticle fs = { p, Fg };
	m_Preg.erase(std::remove(m_Preg.begin(), m_Preg.end(), fs), m_Preg.end());
}

void ForceRegister::remove(RigidBody* r, RigidBodyForceGenerator* Frg) {
	ForceStoredRigidBody fs = { r, Frg };
	m_Rreg.erase(std::remove(m_Rreg.begin(), m_Rreg.end(), fs), m_Rreg.end());
}

void ForceRegister::clear() {
	m_Preg.clear();
	m_Rreg.clear();
}




