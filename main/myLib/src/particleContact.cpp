#include "particleContact.hpp"

using namespace m_engine;

ParticleContact::ParticleContact(Particle* p1, Particle* p2, double c, double penetration) : restitutionCoeff(c), penetration(penetration) {
	//si p1 NULL, renvoie une erreur
	particles[0] = p1;
	particles[1] = p2;
	if (p2 != NULL) {
		n = (particles[0]->getPos() - particles[1]->getPos()).normalize();
	}
	else {
		n = Vector3D(0, 0, 1);
	}

}

double ParticleContact::calculVs() const {

	if (particles[1] != NULL) {
		double va = particles[0]->getVel().scalar(n);
		double vb = particles[1]->getVel().scalar(n);

		return (va - vb);
	}
	else {
		//cas du sol (on considère le sol à z=0)
		double va = particles[0]->getVel().scalar(n);
		
		return va;
	}
	

}

void ParticleContact::resolve(double time) {
	resolveVelocity(time);
	resolvePenetration(time);
}

void ParticleContact::resolveVelocity(double time) {
	Vector3D vs = -restitutionCoeff * calculVs() * n;
	if (particles[1] != NULL) { //cas sans sol
		Vector3D delta = particles[0]->getInversMass() / particles[1]->getInversMass() * vs;
		particles[0]->setVel(particles[0]->getVel() + delta);
	}
	else { // cas du sol
		//TODO
	}
}

void ParticleContact::resolvePenetration(double time) {
	Vector3D delta;
	if (particles[1] == NULL) { //cas du sol : le sol ne bouge pas
		delta = penetration*n;
	}
	else {
		double ma = 1 / particles[0]->getInversMass();
		double mb = 1 / particles[1]->getInversMass();
		delta = mb / (ma + mb) * penetration * n;
	}
	
	particles[0]->setPos(particles[0]->getPos() + delta);
}
