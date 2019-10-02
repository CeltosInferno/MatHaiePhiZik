#include "particleContact.hpp"

using namespace m_engine;

ParticleContact::ParticleContact(Particle* p1, Particle* p2, double c) : restitutionCoeff(c) {
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

		return -restitutionCoeff * (va - vb);
	}
	else {
		//cas du sol (on considère le sol à z=0)
		double va = particles[0]->getVel().scalar(n);
		
		return -restitutionCoeff * va;
	}
	

}