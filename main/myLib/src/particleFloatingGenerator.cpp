#include "particleFloatingGenerator.hpp"

using namespace m_engine;

void ParticleFloatingGenerator::updateForce(Particle& p, double time) {
	double z = p.getPos()[2]; //change 2 by 1 if y is the height
	Vector3D f;
	if (z >= waterHeight + radius) { //particle above the water
		//f=0
	}
	else if (z <= waterHeight - radius) { //particle under the water
		f[2] = -volume;
	}
	else {
		f[2] = -volume * ((waterHeight - z + radius) / (2 * radius));
	}
	p.addForce(f);
}
