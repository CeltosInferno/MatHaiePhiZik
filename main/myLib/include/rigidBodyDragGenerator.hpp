#ifndef RIGIDBODY_DRAG_GENERATOR
#define RIGIDBODY_DRAG_GENERATOR

#include "rigidBodyForceGenerator.hpp"

/*
	Force representing the friction
*/

namespace m_engine {

	class RigidBodyDragGenerator : public RigidBodyForceGenerator {
	public:
		RigidBodyDragGenerator(double k1, double k2) : k1(k1), k2(k2) {};
		~RigidBodyDragGenerator() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(RigidBody& r, double time);

	private:
		double k1, k2;

	};

}

#endif