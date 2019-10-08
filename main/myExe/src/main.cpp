#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "mainLoop.hpp"

#include "particleGravityGenerator.hpp"

using namespace m_engine;

#define _G 9.81

#define FPS 10

World myWorld;

void arrowKeyEffect(std::string dir) {
	if (dir == "LEFT") {
		for (Particle p : myWorld.particles) {
			
		}
	}
	else if (dir == "RIGHT") {
		std::cout << "A DROITE" << std::endl;
	}
	else if (dir == "UP") {
		std::cout << "EN HAUT" << std::endl;
	}
	else if (dir == "DOWN") {
		std::cout << "EN BAS" << std::endl;
	}
}

bool onStartLoop(double time, int id_iteration) {
	static ParticleGravityGenerator gravityGenerator(Vector3D(0, -_G, 0));

	for (Particle& p : myWorld.particles) {
		myWorld.forceRegister.add(&p, &gravityGenerator);
	}
	return true;
}

int main() {
	MainLoop myMainLoop(myWorld, FPS);
	myMainLoop.setStartFrameFun(onStartLoop);

	myWorld.start();

	char entry = 'a';
	while (entry != '1' && entry != '2' && entry != '3' && entry != '4')
	{
		std::cout << "choisissez un projetile" << std::endl << "1 : sans damping" << std::endl << "2 : 0.99 de damping" << std::endl << "3 : 0.9 de damping" << std::endl << "4 : 0.5 de damping sans gravité" << std::endl << "choix :";
		std:: cin >> entry;
	}

	switch (entry) {
	case '1' :
		myWorld.addParticle(Particle(2, 1, Vector3D(0, 0, 0), Vector3D(0, 15, 0), Vector3D(0, -9.8, 0)));
		break;
	case '2' :
		myWorld.addParticle(Particle(1, 0.99, Vector3D(0, 1, 0), Vector3D(0, 10, 0), Vector3D(0, -9.8, 0)));
		break;
	case '3':
		myWorld.addParticle(Particle(3, 0.9, Vector3D(0, 2, 0), Vector3D(0, 15, 0), Vector3D(0, -9.8, 0)));
		break;
	case '4':
		myWorld.addParticle(Particle(3, 1, Vector3D(0, 2, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0)));
		break;
	}

	myMainLoop.execute();

	return 0;
}
