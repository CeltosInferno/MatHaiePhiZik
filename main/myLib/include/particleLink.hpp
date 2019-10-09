#ifndef PARTICLE_LINK
#define PARTICLE_LINK

#include "particleContactGenerator.hpp"
#include "particle.hpp"

namespace m_engine {
	class ParticleLink : virtual public ParticleContactGenerator {
	public:
		ParticleLink(Particle* pa, Particle* pb);
		virtual ~ParticleLink() {}

		virtual void addContact();

		double currentLength() const;
	private:
		Particle* particles[2];
	};
}


#endif