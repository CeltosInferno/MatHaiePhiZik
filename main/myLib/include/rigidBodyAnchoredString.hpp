#ifndef RIGIDBODY_ANCHORED_STRING
#define RIGIDBODY_ANCHORED_STRING

#include "rigidBodyForceGenerator.hpp"

/*
	Force representing a particle anchored to a point
*/

namespace m_engine {

	class RigidBodyAnchoredString : public RigidBodyForceGenerator {
	protected:
		Vector3D m_ancrage;
		double m_K;
		double m_l0;
	public:
		//ancrage must be in local coordinates
		RigidBodyAnchoredString(const Vector3D& ancrage, double K, double l0);
		virtual ~RigidBodyAnchoredString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(RigidBody& r, double time);

		inline void setAncrage(const Vector3D& v) { m_ancrage = v; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
	};

}

#endif