#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "mainLoop.hpp"

#include "particleGravityGenerator.hpp"
#include "particleFloatingGenerator.hpp"

using namespace m_engine;

#define _G 9.81
#define _ArrowIntensity 20

#define FPS 10

World myWorld;

void arrowKeyEffect(std::string dir) {
	if (dir == "LEFT") {
		std::cout << "COUCOU" << std::endl;
		for (Particle& p : myWorld.particles) {
			p.addForce(Vector3D(-_ArrowIntensity,0,0));
		}
	}
	if (dir == "RIGHT") {
		for (Particle& p : myWorld.particles) {
			p.addForce(Vector3D(_ArrowIntensity, 0, 0));
		}
	}
	if (dir == "UP") {
		for (Particle& p : myWorld.particles) {
			p.addForce(Vector3D(0, 0, _ArrowIntensity));
		}
	}
	if (dir == "DOWN") {
		for (Particle& p : myWorld.particles) {
			p.addForce(Vector3D(0, 0, -_ArrowIntensity));
		}
	}
}

bool onStartLoop(double time, int id_iteration) {
	static ParticleGravityGenerator gravityGenerator(Vector3D(0, 0, -_G));
	//static ParticleFloatingGenerator floatingGenerator();

	for (Particle& p : myWorld.particles) {
		//myWorld.forceRegister.add(&p, &gravityGenerator);
		//myWorld.forceRegister.add(&p, &floatingGenerator);
	}
	return true;
}

int main() {
	MainLoop myMainLoop(myWorld, FPS);
	myMainLoop.setStartFrameFun(onStartLoop);

	myWorld.setInput(arrowKeyEffect);
	myWorld.start();

	char entry = 'a';
	while (entry != '1' && entry != '2' && entry != '3' && entry != '4')
	{
		std::cout << "choisissez un projetile" << std::endl << "1 : sans damping" << std::endl << "2 : 0.99 de damping" << std::endl << "3 : 0.9 de damping" << std::endl << "4 : 0.5 de damping sans gravité" << std::endl << "choix :";
		std:: cin >> entry;
	}

	switch (entry) {
	case '1' :
		myWorld.addParticle(Particle(2, 1, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		break;
	case '2' :
		myWorld.addParticle(Particle(1, 0.99, Vector3D(0, 1, 0), Vector3D(10, 0, 0), Vector3D(0, -9.8, 0)));
		break;
	case '3':
		myWorld.addParticle(Particle(3, 0.9, Vector3D(0, 2, 0), Vector3D(15, 0, 0), Vector3D(0, -9.8, 0)));
		break;
	case '4':
		myWorld.addParticle(Particle(3, 1, Vector3D(0, 2, 0), Vector3D(10, 0, 10), Vector3D(0, 0, 0)));
		break;
	}

	myMainLoop.execute();

	return 0;
}
