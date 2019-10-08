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
		//cas du sol (on consid�re le sol � z=0)
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
		double m0 = 1/particles[0]->getInversMass();
		double m1 = 1 / particles[1]->getInversMass();
		particles[0]->setVel(particles[0]->getVel() + 2*m1/(m0+m1) * vs);
		particles[1]->setVel(particles[1]->getVel() - 2*m0/(m0+m1) * vs);
	}
	else { // cas du sol
		particles[0]->setVel(particles[0]->getVel() + 2 * vs);
	}
}

void ParticleContact::resolvePenetration(double time) {
	if (particles[1] == NULL) { //cas du sol : le sol ne bouge pas
		particles[0]->setPos(particles[0]->getPos() + penetration*n);
	}
	else {
		double ma = 1 / particles[0]->getInversMass();
		double mb = 1 / particles[1]->getInversMass();
		Vector3D delta0 = mb / (ma + mb) * penetration * n;
		Vector3D delta1 = -ma / (ma + mb) * penetration * n;
		particles[0]->setPos(particles[0]->getPos() + delta0);
		particles[1]->setPos(particles[1]->getPos() + delta1);
	}
	
	
}
