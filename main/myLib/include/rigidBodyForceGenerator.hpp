#ifndef RIGIDBODY_FORCE_GENERATOR
#define RIGIDBODY_FORCE_GENERATOR

#include "rigidBody.hpp"

/*
	Interface used to generate a force for a rigidBody (the kind of force is represented by the children classes)
*/

namespace m_engine {

	class RigidBodyForceGenerator {
	public:
		virtual ~RigidBodyForceGenerator() {};

		//generate a force for the rigidBody concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(RigidBody& r, double time) = 0;
	};

}

#endif