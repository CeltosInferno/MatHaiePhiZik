#include "rigidBodyGravityGenerator.hpp"

using namespace m_engine;


void RigidBodyGravityGenerator:: updateForce(RigidBody& r, double time) {
	r.addForceAtBodyPoint(r.getInversMass() * gravity);
}