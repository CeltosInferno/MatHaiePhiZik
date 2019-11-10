#include "rigidBodyFloatingGenerator.hpp"

using namespace m_engine;

void RigidBodyFloatingGenerator::updateForce(RigidBody& r, double time) {
	double z = r.getPos()[2]; //change 2 by 1 if y is the height
	Vector3D f;
	if (z >= waterHeight + radius) { //particle above the water
		//f=0
	}
	else if (z <= waterHeight - radius) { //particle under the water
		f[2] = volume;
	}
	else {
		f[2] = volume * ((waterHeight - z + radius) / (2 * radius));
	}
	r.addForceAtBodyPoint(f);
}
