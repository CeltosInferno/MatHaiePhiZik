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

#define _G 100
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

//solve the collision (weak solution) works only when collision on x
void veryBadCollisionRigidBody(RigidBody& rb1, RigidBody& rb2, double penetration, const Vector3D& n) {

	double ma = 1 / rb1.getInversMass();
	double mb = 1 / rb2.getInversMass();
	Vector3D delta0 = -mb / (ma + mb) * penetration * n;
	Vector3D delta1 = ma / (ma + mb) * penetration * n;
	//déplacement des 2 particules
	rb1.setPos(rb1.getPos() + delta0);
	rb2.setPos(rb2.getPos() + delta1);
}

void checkCollisionAndSolve() {
	RigidBody& rb1 = myWorld.rigidbodies[0];
	RigidBody& rb2 = myWorld.rigidbodies[1];
	double penetration = (rb1.dx / 2 + rb2.dx / 2 - rb1.getPos().distance(rb2.getPos()));
	//std::cout << penetration << std::endl;
	//std::cout << rb1.getPos() << ", " << rb2.getPos() << std::endl;
	if (penetration >= 0) {
		Vector3D n(1, 0, 0);

		veryBadCollisionRigidBody(rb1, rb2, penetration, n);
		rb1.addForceAtGlobalPoint(Vector3D(-30), rb2.getPos() - Vector3D(rb2.dx/2));
		rb2.addForceAtGlobalPoint(Vector3D(30), rb1.getPos() + Vector3D(rb1.dx / 2));
	}
}

//This function will be bind with the main loop and will be executed at the beginning of each frame
bool onStartLoop(double time, int id_iteration) {
	switch (entry) {
	case '1':
		break;
	case'2':
		checkCollisionAndSolve();
		break;
	}
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

	//Displaying in a terminal the demonstrations options
	while (entry != '0' && entry != '1' && entry != '2')
	{
		std::cout << "choisissez une démonstration" << std::endl
			<< "0 : Quitter" << std::endl
			<< "1 : RigidBody avec gravité" << std::endl
			<< "2 : Collision de 2 Vehicules" << std::endl
			<< "choix :";
		std::cin >> entry;
	}

	switch (entry) {
		//Floating demonstration
	case '1':
		myMainLoop.setZoom(80);
		//setting up particles
		myWorld.addRigidBody(RigidBody(1, 1, 3, 10, 0.95, 0.95, Vector3D(-30, 0, 0), Vector3D(4, 5, 0), Quaternion::FormAxisAngle(M_PI / 3.0, Vector3D(1, 0, 0).normalize()), Vector3D(1, 1, 0)));
		myWorld.addRigidBody(RigidBody(1, 1, 3, 10, 0.95, 0.95, Vector3D(30, 0, 0), Vector3D(0, 0, 0), Quaternion::FormAxisAngle(2 * M_PI / 5.0, Vector3D(1, 0, 0).normalize()), Vector3D()));
		//recording force generators
		rigb_gen.push_back(&gravityGenerator);
		//setting up input's reaction
		myWorld.setInput(arrowKeyEffect);
		break;
		//String demonstration
	case '2':
		myMainLoop.setZoom(20);
		myWorld.addRigidBody(RigidBody(3, 2, 1, 1, 0.95, 0.95, 
							Vector3D(-10, 0, 0), Vector3D(5, 0, 0), Quaternion::FormAxisAngle(0, Vector3D(1, 0, 0).normalize()), Vector3D()));
		myWorld.addRigidBody(RigidBody(3, 2.5, 1, 1, 0.95, 0.95, 
							Vector3D(10, 1, 0), Vector3D(-5, 0, 0), Quaternion::FormAxisAngle(0, Vector3D(1, 0, 0).normalize()), Vector3D()));
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