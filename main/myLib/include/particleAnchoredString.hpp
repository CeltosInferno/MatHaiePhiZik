#ifndef PARTICLE_ANCHORED_STRING
#define PARTICLE_ANCHORED_STRING

#include "particleForceGenerator.hpp"

/*
	Force representing a particle anchored to a point
*/

namespace m_engine {

	class ParticleAnchoredString : public ParticleForceGenerator {
	protected:
		Vector3D m_ancrage;
		double m_K;
		double m_l0;
	public:
		ParticleAnchoredString(const Vector3D& ancrage, double K, double l0);
		virtual ~ParticleAnchoredString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(Particle& p, double time);

		inline void setAncrage(const Vector3D& v) { m_ancrage = v; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
	};

}

#endif