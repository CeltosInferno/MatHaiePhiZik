#ifndef RIGIDBODY_GRAVITY_GENERATOR
#define RIGIDBODY_GRAVITY_GENERATOR

#include "rigidBodyForceGenerator.hpp"

/*
	Force representing the gravity
*/

namespace m_engine {

	class RigidBodyGravityGenerator : public RigidBodyForceGenerator{
	public:
		RigidBodyGravityGenerator(const Vector3D& g) : gravity(g) {};
		~RigidBodyGravityGenerator() {};

		//generate a force for the rigidBody concerned, time is the duration of a frame (in seconds)
		void updateForce(RigidBody& r, double time);

	private :
		Vector3D gravity;
	};

}

#endif