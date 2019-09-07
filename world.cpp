#include "world.hpp"
#include <iostream>



using namespace m_engine;

World::World() {

}

World::~World() {

}

void World::start() {
	particles.push_back(Particle(2, 1, 0, 0, 0, 0, 30, 0, 0, -0.0098, 0));
}

void World::update(long time) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].integrate(time);
	}
}

void World::render() {
	for (Particle particle : particles) {
		particle.render();
	}
	std::cout << std::endl;
}

void World::addParticle(Particle part) {
	particles.push_back(part);
}