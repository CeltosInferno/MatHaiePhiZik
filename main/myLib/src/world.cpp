#include "world.hpp"
#include <iostream>



using namespace m_engine;

World::World() {

}

World::~World() {

}

void World::start() {}

void World::update(double time) {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].integrate(time);
	}
}

void World::render() {
	for (Particle& particle : particles) {
		std::cout << particle;
	}
	std::cout << std::endl;
}

void World::addParticle(const Particle& part) {
	particles.push_back(part);
}
