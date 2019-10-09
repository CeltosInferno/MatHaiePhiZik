#include "particleContactResolver.hpp"

#include <iostream>

using namespace m_engine;

ParticleContactResolver::ParticleContactResolver() {

}

bool ParticleContactResolver::resolveCollisions(double time, std::vector<Particle>& particles) {
	int i = 0;
	int nb_iteration = particles.size() * particles.size();
	do {
		//on regarde les collisions potentielles
		checkForCollision(particles);
		if (collisions.size() == 0) return true; //plus de collisions
		std::cout << "got " << collisions.size() << "collisions" << std::endl;
		//on cherche quelle collision traiter, 
		//ici celle avec la vitesse de separation la plus
		//faible (penetration rapide)
		double minSpeed = separationSpeeds[0];
		int firstCollision = 0;
		for (int j = 1; j < separationSpeeds.size(); j++) {
			double speed = separationSpeeds[j];
			if (speed < minSpeed) {
				minSpeed = speed;
				firstCollision = j;
			}
		}
		//on resout la collision
		collisions[firstCollision].resolve(time);

		i++;
	} while (i < nb_iteration && collisions.size() > 0);
	return false;
}

void ParticleContactResolver::checkForCollision(std::vector<Particle>& particles) {
	//on nettoie les stockages
	collisions.clear();
	separationSpeeds.clear();
	for (int i = 0; i < particles.size(); i++) {
		//test avec le sol
		Particle* p1 = &particles[i];
		if (isColliding(p1, &ParticleContact::Floor)) {
			ParticleContact Pc(p1, &ParticleContact::Floor, 1, getPenetration(p1, &ParticleContact::Floor));
			collisions.push_back(Pc);
			separationSpeeds.push_back(Pc.calculVs());
		}
		//test avec les autres particules
		for (int j = i+1; j < particles.size(); j++) {
			Particle* p2 = &particles[j];
			if (isColliding(p1, p2)) {
				ParticleContact Pc(p1, p2, 1, getPenetration(p1, p2));
				collisions.push_back(Pc);
				separationSpeeds.push_back(Pc.calculVs());
			}
		}
	}
}

double ParticleContactResolver::getPenetration(const Particle* pa, const Particle* pb) {
	if (pb == &ParticleContact::Floor) {
		double floorHeight = ParticleContact::Floor.getPos().scalar(ParticleContact::NormalFloor);
		double particuleHeight = pa->getPos().scalar(ParticleContact::NormalFloor);
		return (pa->getRadius() + floorHeight - particuleHeight);
	}
	else {
		return (pa->getRadius() + pb->getRadius() - pa->getPos().distance(pb->getPos()));
	}
}

bool ParticleContactResolver::isColliding(const Particle* pa, const Particle* pb) {
	/*std::cout << "penetration between :" << pa->getPos() << ", "
		<< pb->getPos()  << " :" << getPenetration(pa, pb)
		<< ", dist :" << pa->getPos().distance(pb->getPos()) 
		<< std::endl;*/
	//on ne g'ere pas les collisions avec une particule de rayon nul
	if (pa->getRadius() <= 0 || 
		(pb != &ParticleContact::Floor && pb->getRadius() <= 0)) 
		return false;
	return getPenetration(pa, pb) > 0;
}


