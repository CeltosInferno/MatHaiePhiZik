#include "world.hpp"
#include "vector3d.hpp"
#include <iostream>



using namespace m_engine;

World::World() {

}

World::~World() {

}

void World::start() {
	particles.push_back(Particle(2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0));
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
	//internal rendering
	Vector3D temp;
	for (Particle& particle : particles) {
		temp = particle.getPos();
		int x = int (temp.x);
		int y = int(temp.y);
		if(x >=0 && x <=9 && y >=0 && y <=9){
			m_world[x][y] = 'o';
		}
	}
	//graphical rendering
	for(unsigned int i = 0; i<10; i++ ){
		for(unsigned int j=0; j<10; j++){
			std::cout<< m_world[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void World::addParticle(const Particle& part) {
	particles.push_back(part);
}
