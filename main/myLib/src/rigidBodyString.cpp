#include "rigidBodyString.hpp"

using namespace m_engine;

RigidBodyString::RigidBodyString(RigidBody& RBancrage, const Vector3D& Vancrage, double K, double l0) :
	m_RBancrage(&RBancrage), m_K(K), m_l0(l0),m_Vancrage(&Vancrage)
{}

void RigidBodyString::updateForce(RigidBody& r, double time) {
	Vector3D delta = r.getPos() - m_RBancrage->localToGlobal(*m_Vancrage);
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	r.addForceAtBodyPoint(force);
}
