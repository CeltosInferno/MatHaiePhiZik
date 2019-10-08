#include "forceRegister.hpp"
#include <algorithm>

using namespace m_engine;

void ForceRegister::add(Particle* p, ParticleForceGenerator* Fg) {
	ForceStored fs = { p, Fg };
	m_reg.push_back(fs);
}

void ForceRegister::applyForces(double time) {
	for (ForceStored fs : m_reg) {
		fs.Fg->updateForce(*(fs.p), time);
	}
}

void ForceRegister::remove(Particle* p, ParticleForceGenerator* Fg) {
	ForceStored fs = { p, Fg };
	m_reg.erase(std::remove(m_reg.begin(), m_reg.end(), fs), m_reg.end());
}

void ForceRegister::clear() {
	m_reg.clear();
}




