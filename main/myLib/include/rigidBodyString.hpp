#ifndef RIGIDBODY_STRING
#define RIGIDBODY_STRING

#include "rigidBodyForceGenerator.hpp"

/*
	Force representing a rigidBody anchored to another
*/

namespace m_engine {

	class RigidBodyString : public RigidBodyForceGenerator {
	protected:
		RigidBody* m_RBancrage;
		const Vector3D* m_Vancrage;
		double m_K;
		double m_l0;
	public:
		RigidBodyString(RigidBody& RBancrage,const Vector3D& Vancrage, double K, double l0);
		virtual ~RigidBodyString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(RigidBody& p, double time);

		inline void setRBAncrage(RigidBody& p) { m_RBancrage = &p; }
		inline void setLocalAncrage(const Vector3D& V) { m_Vancrage = &V; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
	};

}

#endif