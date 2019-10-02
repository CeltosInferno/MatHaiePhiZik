#ifndef PARTICLE_STIFF_SPRING
#define PARTICLE_STIFF_SPRING

#include "particleForceGenerator.hpp"


namespace m_engine {

	class ParticleStiffSpring : public ParticleForceGenerator {
	public:
		ParticleStiffSpring(Vector3D anc, double k, double damp) : anchor(anc), k(k), damping(damp) {};
		~ParticleStiffSpring() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(Particle& p, double time);

	private:
		Vector3D anchor;
		double k, damping;

	};

}

#endif