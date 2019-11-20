#define _USE_MATH_DEFINES

#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "rigidBody.hpp"
#include "mainLoop.hpp"
#include "quaternion.hpp"

#include "particleGravityGenerator.hpp"
#include "particleFloatingGenerator.hpp"
#include "particleString.hpp"
#include "rigidBodyGravityGenerator.hpp"

using namespace m_engine;

#define _G 1
#define _ArrowIntensity 100

#define FPS 30

World myWorld;

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
		for (RigidBodyForceGenerator* g : rigb_gen) {
			for (RigidBody& p : myWorld.rigidbodies) {
				myWorld.forceRegister.add(&p, g);
			}
		}
		break;
	case'2':
		break;
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

	//Displaying in a terminal the demonstrations options
	while (entry != '0' && entry != '1' && entry != '2')
	{
		std::cout << "choisissez une démonstration" << std::endl
			<< "0 : Quitter" << std::endl
			<< "1 : RigidBody avec gravité" << std::endl
			//<< "2 : Deux particules avec ressort" << std::endl
			<< "choix :";
		std::cin >> entry;
	}

	switch (entry) {
		//Floating demonstration
	case '1':
		myMainLoop.setZoom(8);
		//setting up particles
		myWorld.addRigidBody(RigidBody(1, 1, 3, 1, 0.95, 0.95, Vector3D(-3, 0, 0), Vector3D(2, 2, 0), Quaternion::FormAxisAngle(M_PI / 3.0, Vector3D(1, 0, 0).normalize()), Vector3D(1, 1, 0)));
		myWorld.addRigidBody(RigidBody(1, 1, 3, 1, 0.95, 0.95, Vector3D(3, 0, 0), Vector3D(0, 0, 0), Quaternion::FormAxisAngle(2 * M_PI / 5.0, Vector3D(1, 0, 0).normalize()), Vector3D()));
		//recording force generators
		rigb_gen.push_back(&gravityGenerator);
		//setting up input's reaction
		myWorld.setInput(arrowKeyEffect);
		break;
		//String demonstration
	//case '2':

	//	break;
	default:
		return 0;
	}


	//starting the world
	myWorld.start();

	//starting execution
	myMainLoop.execute();

	return 0;
}