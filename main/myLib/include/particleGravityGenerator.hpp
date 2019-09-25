#ifndef PARTICLE_GRAVITY_GENERATOR
#define PARTICLE_GRAVITY_GENERATOR

#include "particleForceGenerator.hpp"


namespace m_engine {

	class ParticleGravityGenerator : public ParticleForceGenerator{
	public:
		ParticleGravityGenerator(const Vector3D& g) : gravity(g) {};
		~ParticleGravityGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(Particle& p, double time);

	private :
		Vector3D gravity;

	};

}

#endif