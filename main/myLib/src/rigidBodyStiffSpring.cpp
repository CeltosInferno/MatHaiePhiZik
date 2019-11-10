#include "rigidBodyStiffSpring.hpp"

using namespace m_engine;

void RigidBodyStiffSpring::updateForce(RigidBody& r, double time) {
	Vector3D f;
	double gamma = sqrt(4 * k - damping * damping) / 2;
	Vector3D c = damping / (2 * gamma) * r.getPos() + r.getVel() / gamma;

	f = (r.getPos() * cos(gamma * time) + c * sin(gamma * time)) * exp(-damping * time / 2);
	
	r.addForceAtBodyPoint(f);
}