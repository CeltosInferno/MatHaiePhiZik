#ifndef PARTICLE_FLOATING_GENERATOR
#define PARTICLE_FLOATING_GENERATOR

#include "particleForceGenerator.hpp"


namespace m_engine {

	class ParticleFloatingGenerator : public ParticleForceGenerator {
	public:
		ParticleFloatingGenerator(double r, double v, double h) : radius(r), volume(v), waterHeight(h) {};
		~ParticleFloatingGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(Particle& p, double time);

	private:
		double radius, volume, waterHeight;

	};

}

#endif