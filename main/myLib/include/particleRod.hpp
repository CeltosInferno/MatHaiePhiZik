#ifndef PARTICLE_ROD
#define PARTICLE_ROD

#include "particleLink.hpp"

namespace m_engine {
	class ParticleRod : public ParticleLink {
	public:
		ParticleRod(Particle* pa, Particle* pb, double length);
		virtual ~ParticleRod() {}

		virtual void addContact();

	private:
		double m_length;
	};
}


#endif