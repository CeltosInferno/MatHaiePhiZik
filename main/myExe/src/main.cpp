#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "mainLoop.hpp"

using namespace m_engine;

#define FPS 30

int main() {
  
	World myWorld;
	MainLoop myMainLoop(myWorld, FPS);

	myWorld.start();

	char entry = 'a';
	while (entry != '1' && entry != '2' && entry != '3' && entry != '4')
	{
		std::cout << "choisissez un projetil" << std::endl << "1 : sans damping" << std::endl << "2 : 0.99 de damping" << std::endl << "3 : 0.9 de damping" << std::endl << "4 : 0.5 de damping sans gravité" << std::endl << "choix :";
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
		myWorld.addParticle(Particle(3, 0.5, Vector3D(0, 2, 0), Vector3D(0, 10, 0), Vector3D(0, 0, 0)));
		break;
	}

	myMainLoop.execute();

	return 0;
}
