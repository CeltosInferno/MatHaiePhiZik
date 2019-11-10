#ifndef RIGIDBODY_STIFF_SPRING
#define RIGIDBODY_STIFF_SPRING

#include "rigidBodyForceGenerator.hpp"

/*
	Force representing an harmonic movement
*/

namespace m_engine {

	class RigidBodyStiffSpring : public RigidBodyForceGenerator {
	public:
		RigidBodyStiffSpring(Vector3D anc, double k, double damp) : anchor(anc), k(k), damping(damp) {};
		~RigidBodyStiffSpring() {};

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		void updateForce(RigidBody& r, double time);

	private:
		Vector3D anchor;
		double k, damping;

	};

}

#endif