#ifndef PARTICLE_DRAG_GENERATOR
#define PARTICLE_DRAG_GENERATOR

#include "particleForceGenerator.hpp"


namespace m_engine {

	class ParticleDragGenerator : public ParticleForceGenerator {
	public:
		ParticleDragGenerator(double k1, double k2) : k1(k1), k2(k2) {};
		~ParticleDragGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(Particle& p, double time);

	private:
		double k1, k2;

	};

}

#endif