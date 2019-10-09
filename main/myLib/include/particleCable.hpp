#ifndef PARTICLE_CABLE
#define PARTICLE_CABLE

#include "particleLink.hpp"

namespace m_engine {
	class ParticleCable : public ParticleLink {
	public:
		ParticleCable(Particle* pa, Particle* pb, double length, double restitution);
		virtual ~ParticleCable() {}

		virtual void addContact();

	private:
		double m_length;
		double m_restitution;
	};
}


#endif