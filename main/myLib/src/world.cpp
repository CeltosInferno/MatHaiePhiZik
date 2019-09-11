#include "world.hpp"
#include "vector3d.hpp"
#include <iostream>

#define LINES 10
#define COLUMNS 20

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

void World::renderBash() {
	//world initialization
	char m_world[LINES][COLUMNS];
	for(unsigned int i = 0; i<LINES; i++ ){
		for(unsigned int j=0; j<COLUMNS; j++){
			m_world[i][j] = ' ';
		}
	}
	//internal rendering
	Vector3D temp;
	for (Particle& particle : particles) {
		temp = particle.getPos();
		int x = int (temp.x);
		int y = int(temp.y);
		if(x >=0 && x < LINES && y >=0 && y < COLUMNS){
			m_world[x][y] = 'o';
		}
	}
	//graphical rendering
	for(unsigned int i = 0; i<LINES; i++ ){
		for(unsigned int j=0; j<COLUMNS; j++){
			std::cout<< m_world[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void World::addParticle(const Particle& part) {
	particles.push_back(part);
}
