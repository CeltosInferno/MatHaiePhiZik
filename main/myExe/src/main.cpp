#define _USE_MATH_DEFINES

#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "rigidBody.hpp"
#include "mainLoop.hpp"
#include "quaternion.hpp"
#include "plane.hpp"

#include "particleGravityGenerator.hpp"
#include "particleFloatingGenerator.hpp"
#include "particleString.hpp"
#include "rigidBodyGravityGenerator.hpp"

using namespace m_engine;

#define _G 100
#define _ArrowIntensity 100

#define FPS 30

World myWorld;

/*
Ce main correspond à la phase 3
Implémentation des rigidBody et des forces spécifiques
*/


std::vector<ParticleForceGenerator*> part_gen;
std::vector<RigidBodyForceGenerator*> rigb_gen;
static char entry = 'a';

void arrowKeyEffect(std::string dir) {
	if (dir == "LEFT") {
		for (Particle& p : myWorld.particles) {
			p.addForce(Vector3D(-_ArrowIntensity, 0, 0));
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


//This function will be bind with the main loop and will be executed at the beginning of each frame
bool onStartLoop(double time, int id_iteration) {
	switch (entry) {
	case '1':
		break;
	case'2':
		break;
	}
	//we apply all registered forces each frame
	for (RigidBodyForceGenerator* g : rigb_gen) {
		for (RigidBody& p : myWorld.rigidbodies) {
			myWorld.forceRegister.add(&p, g);
		}
	}
	return true;
}


//The main
int main() {
	//Creating the main loop
	MainLoop myMainLoop(myWorld, FPS);
	//Setting up the main loop
	myMainLoop.setStartFrameFun(onStartLoop);


	static RigidBodyGravityGenerator gravityGenerator(Vector3D(0, -_G, 0));

	RigidBody rb (3, 2, 1, 1, 0.95, 0.2, Vector3D(-1, 0, 0), Vector3D(5, 0, 0));
	//std::cout << rb.getPos() << std::endl;
	RigidBody rb2(1, 1, 1, 1, Vector3D(9, 0, 0));
	Plane p = Plane(11, Vector3D(1, 0, 0));
	//Displaying in a terminal the demonstrations options
	while (entry != '0' && entry != '1')
	{
		std::cout << "choisissez une démonstration" << std::endl
			<< "0 : Quitter" << std::endl
			<< "1 : Collision RigidBody/Plan" << std::endl
			<< "choix :";
		std::cin >> entry;
	}

	switch (entry) {
		//Floati
	case '1':
		myMainLoop.setZoom(20);
		myWorld.addRigidBody(rb);
		//myWorld.addRigidBody(rb2);
		myWorld.addPlane(p);
		myWorld.setInput(arrowKeyEffect);
		break;
	default:
		return 0;
	}


	//starting the world
	myWorld.start();

	//starting execution
	myMainLoop.execute();

	return 0;
}