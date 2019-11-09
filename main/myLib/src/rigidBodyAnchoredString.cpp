#include "rigidBodyAnchoredString.hpp"

using namespace m_engine;

RigidBodyAnchoredString::RigidBodyAnchoredString(const Vector3D& ancrage, double K, double l0): 
	m_ancrage(ancrage), m_K(K), m_l0(l0)
{}

void RigidBodyAnchoredString::updateForce(RigidBody& r, double time) {
	Vector3D delta = r.getPos() - r.localToGlobal(m_ancrage);
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	r.addForceAtLocalPoint(force,m_ancrage);
}

