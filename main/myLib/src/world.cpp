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
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].integrate(time);
	}
}

void World::renderBash() {
	//world initialization
	char m_world[10][10];
	for(unsigned int i = 0; i<10; i++ ){
		for(unsigned int j=0; j<10; j++){
			m_world[i][j] = ' ';
		}
	}
	
	for (Particle& particle : particles) {
		particle.render();
	}
	std::cout << std::endl;
}

void World::addParticle(const Particle& part) {
	particles.push_back(part);
}
