#ifndef RIGIDBODY_FLOATING_GENERATOR
#define RIGIDBODY_FLOATING_GENERATOR

#include "rigidBodyForceGenerator.hpp"


namespace m_engine {

	/*
		Represent a force applied by a liquid on a particle
	*/

	class RigidBodyFloatingGenerator : public RigidBodyForceGenerator {
	public:
		RigidBodyFloatingGenerator(double r, double v, double h) : radius(r), volume(v), waterHeight(h) {};
		~RigidBodyFloatingGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(RigidBody& r, double time);

	private:
		double radius, volume, waterHeight;

	};

}

#endif