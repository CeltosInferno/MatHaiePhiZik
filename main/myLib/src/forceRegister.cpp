#include "forceRegister.hpp"
#include <algorithm>

using namespace m_engine;

bool operator==(const ForceRegister::ForceStored& f1, const ForceRegister::ForceStored& f2) {
	return (&f1.p == &f2.p) && (&f1.Fg == &f2.Fg);
}

void ForceRegister::add(Particle& p, ParticleForceGenerator& Fg) {
	ForceStored fs = { p, Fg };
	m_reg.push_back(fs);
}

void ForceRegister::remove(Particle& p, ParticleForceGenerator& Fg) {
	ForceStored fs = { p, Fg };
	//todo
	//m_reg.erase(std::remove(m_reg.begin(), m_reg.end(), fs), m_reg.end());
}

void ForceRegister::clear() {
	m_reg.clear();
}




