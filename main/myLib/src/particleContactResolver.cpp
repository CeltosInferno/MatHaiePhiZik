#include "particleContactResolver.hpp"

using namespace m_engine;

//on defini le sol comme suit
static Particle Floor(1,1, 0,0,-10);
static Vector3D normalFloor(0,0,1);

ParticleContactResolver::ParticleContactResolver() {

}

bool ParticleContactResolver::resolveCollisions(double time, std::vector<Particle>& particles) {
	int i = 0;
	int nb_iteration = particles.size() * particles.size();
	do {
		//on regarde les collisions potentielles
		checkForCollision(particles);
		if (collisions.size() == 0) return true; //plus de collisions

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
		if (isColliding(p1, &Floor)) {
			ParticleContact Pc(p1, &Floor, 1, getPenetration(p1, &Floor));
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
	if (pb == &Floor) {
		double floorHeight = Floor.getPos().scalar(normalFloor);
		double particuleHeight = pa->getPos().scalar(normalFloor);
		return (pa->getRadius() + floorHeight - particuleHeight);
	}
	else {
		return (pa->getRadius() + pb->getRadius() - pa->getPos().distance(pb->getPos()));
	}
}

bool ParticleContactResolver::isColliding(const Particle* pa, const Particle* pb) {
	return getPenetration(pa, pb) > 0;
}


