#include "rigidBodyElasticString.hpp"

using namespace m_engine;

RigidBodyElasticString::RigidBodyElasticString(const RigidBody& ancrage, double K, double l0, const Vector3D& localPoint) :
	m_ancrage(&ancrage), m_K(K), m_l0(l0), m_localPoint(localPoint)
{}

void RigidBodyElasticString::updateForce(RigidBody& r, double time) {
	Vector3D delta = r.getPos() - m_ancrage->getPos();
	double l = delta.norm();
	if (l < m_l0) return; //no attraction, like a rope
	Vector3D force = -m_K * (delta.norm() - m_l0) * delta.normalize();
	r.addForceAtLocalPoint(force, m_localPoint);
}
