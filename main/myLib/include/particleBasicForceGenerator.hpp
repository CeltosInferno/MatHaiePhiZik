#ifndef PARTICLE_BASIC_FORCE_GENERATOR
#define PARTICLE_BASIC_FORCE_GENERATOR

#include "particleForceGenerator.hpp"


namespace m_engine {

	class ParticleBasicForceGenerator : public ParticleForceGenerator {
	public:
		ParticleBasicForceGenerator(const Vector3D& f) : force(f) {};
		~ParticleBasicForceGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(Particle& p, double time);

	private:
		Vector3D force;

	};

}