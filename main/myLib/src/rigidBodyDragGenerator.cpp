#include "rigidBodyDragGenerator.hpp"

using namespace m_engine;

void RigidBodyDragGenerator::updateForce(RigidBody& r, double time) {
	Vector3D vel = r.getVel();
	double velNorm = vel.norm();
	r.addForceAtBodyPoint(-vel.normalize()*(k1*velNorm + k2*velNorm*velNorm));
}
