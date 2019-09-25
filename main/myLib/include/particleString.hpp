#ifndef PARTICLE_STRING
#define PARTICLE_STRING

#include "particleForceGenerator.hpp"

/*
	Force representing a particle anchored to a point
*/

namespace m_engine {

	class ParticleString : public ParticleForceGenerator {
	protected:
		const Particle* m_ancrage;
		double m_K;
		double m_l0;
	public:
		ParticleString(const Particle& ancrage, double K, double l0);
		virtual ~ParticleString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(Particle& p, double time);

		inline void setAncrage(const Particle& p) { m_ancrage = &p; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
	};

}

#endif