#include "world.hpp"
#include "vector3d.hpp"
#include <iostream>

#define LINES 10
#define COLUMNS 20

using namespace m_engine;

void ArrowKeyEffect(std::string dir) {
	if (dir == "LEFT") {
		std::cout << "A GAUCHE" << std::endl;
	}
	else if (dir == "RIGHT"){
		std::cout << "A DROITE" << std::endl;
	}
	else if (dir == "UP") {
		std::cout << "EN HAUT" << std::endl;
	}
	else if (dir == "DOWN") {
		std::cout << "EN BAS" << std::endl;
	}
}

World::World() : renderer(GraphicRenderer(800, 600, "My World")) {
	renderer.OnKeyEvent(ArrowKeyEffect);
};

World::~World() {

}

void World::start() {}

//Add a particle in the world
void World::addParticle(const Particle& part) {
	particles.push_back(part);
}

//Update all the particles of the world
void World::update(double time) {
	forceRegister.applyForces(time);
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].integrate(time);
		particles[i].cleanAccum();
	}
	forceRegister.clear();
	//check for collision
}

//2D rendering in a terminal
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

//2D rendering in OPenGL Window
//return 0 if everithing is OK, 1 if window should or have close
int World::render2DWindow() {
	return renderer.renderCircles(particles);
}