#ifndef PARTICLE_ELASTIC_STRING
#define PARTICLE_ELASTIC_STRING

#include "particleForceGenerator.hpp"

/*
	Force representing a particle anchored to another
	Here, we don't want to have an attractio when the string
	is long, so we add a test
*/

namespace m_engine {

	class ParticleElasticString : public ParticleForceGenerator {
	protected:
		const Particle* m_ancrage;
		double m_K;
		double m_l0;
	public:
		ParticleElasticString(const Particle& ancrage, double K, double l0);
		virtual ~ParticleElasticString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(Particle& p, double time);

		inline void setAncrage(const Particle& p) { m_ancrage = &p; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
	};
}

#endif