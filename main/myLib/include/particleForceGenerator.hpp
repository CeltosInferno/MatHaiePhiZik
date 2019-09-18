#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "particle.hpp"

/*
	Interface used to generate a force for a particle (the kind of force is represented by the children classes)
*/

namespace m_engine {

	class ParticleForceGenerator {
	public:
		virtual ~ParticleForceGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(Particle& p, double time) = 0;
	};

}

#endif