#ifndef RIGIDBODY_ELASTIC_STRING
#define RIGIDBODY_ELASTIC_STRING

#include "rigidBodyForceGenerator.hpp"
#include "vector3d.hpp"

/*
	Force representing a rigidBody anchored to another
	Here, we don't want to have an attraction when the string
	is long, so we add a test
*/

namespace m_engine {

	class RigidBodyElasticString : public RigidBodyForceGenerator {
	protected:
		const RigidBody* m_ancrage;
		double m_K;
		double m_l0;
		Vector3D m_localPoint;
	public:
		RigidBodyElasticString(const RigidBody& ancrage, double K, double l0, const Vector3D& localPoint);
		virtual ~RigidBodyElasticString() {}

		//generate a force for the particle concerned, time is the duration of a frame (in seconds)
		virtual void updateForce(RigidBody& p, double time);

		inline void setAncrage(const RigidBody& p) { m_ancrage = &p; }
		inline void setl0(double l0) { m_l0 = l0; }
		inline void setK(double k) { m_K = k; }
		inline void setLocalPoint(Vector3D point) { m_localPoint = point; }
	};
}

#endif