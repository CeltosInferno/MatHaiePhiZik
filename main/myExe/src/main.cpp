#include <iostream>
#include "world.hpp"
#include "particle.hpp"
#include "mainLoop.hpp"

#include "particleGravityGenerator.hpp"
#include "particleFloatingGenerator.hpp"
#include "particleString.hpp"

using namespace m_engine;

#define _G 40
#define _ArrowIntensity 100

#define FPS 30

World myWorld;
std::vector<ParticleForceGenerator*> all_gen;
static char entry = 'a';

void arrowKeyEffect(std::string dir) {
	if (dir == "LEFT") {
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

void stringControl(std::string dir) {
	if (dir == "LEFT") {
			myWorld.particles[0].addForce(Vector3D(-_ArrowIntensity, 0, 0));
	}
	if (dir == "RIGHT") {
			myWorld.particles[0].addForce(Vector3D(_ArrowIntensity, 0, 0));
	}
	if (dir == "UP") {
			myWorld.particles[0].addForce(Vector3D(0, 0, _ArrowIntensity));
	}
	if (dir == "DOWN") {
			myWorld.particles[0].addForce(Vector3D(0, 0, -_ArrowIntensity));
	}
}


void string_case() {

	static ParticleString bouncingString1(myWorld.particles[1], 0.5, 490);
	static ParticleString bouncingString2(myWorld.particles[0], 0.5, 490);
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingString1);
	myWorld.forceRegister.add(&myWorld.particles[1], &bouncingString2);
}

void blob_case() {

	int Ksubject = 1;
	int Kqueen = 5;

	static ParticleString bouncingStringto0(myWorld.particles[0], Kqueen, 50);
	static ParticleString bouncingStringto1(myWorld.particles[1], Ksubject, 50);
	static ParticleString bouncingStringto2(myWorld.particles[2], Ksubject, 50);
	static ParticleString bouncingStringto3(myWorld.particles[3], Ksubject, 50);
	static ParticleString bouncingStringto4(myWorld.particles[4], Ksubject, 50);


	//Linking the queen particle
	
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingStringto1);
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingStringto2);
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingStringto3);
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingStringto4);
	
	//Linking back the particles
	
	myWorld.forceRegister.add(&myWorld.particles[1], &bouncingStringto0);
	myWorld.forceRegister.add(&myWorld.particles[2], &bouncingStringto0);
	myWorld.forceRegister.add(&myWorld.particles[3], &bouncingStringto0);
	myWorld.forceRegister.add(&myWorld.particles[4], &bouncingStringto0);
	
}



bool onStartLoop(double time, int id_iteration) {

	switch (entry) {
		case '1':
			for (ParticleForceGenerator* g : all_gen) {
				for (Particle& p : myWorld.particles) {
					myWorld.forceRegister.add(&p, g);
				}
			}
			break;
		case'2':
			string_case();
			break;
		case '3':
			blob_case();
			break;
	}
	return true;
}

int main() {
	MainLoop myMainLoop(myWorld, FPS);
	myMainLoop.setStartFrameFun(onStartLoop);


	static ParticleGravityGenerator gravityGenerator(Vector3D(0, 0, -_G));
	static ParticleFloatingGenerator floatingGenerator(10, 100, 0);
	
	int ressort_dumping = 1;

	while (entry != '1' && entry != '2' && entry != '3' && entry != '4')
	{
		std::cout << "choisissez une démonstration" << std::endl << "1 : Floating Generator avec gravité" << std::endl << "2 : Deux particules avec ressort" << std::endl << "3 : Blob" << std::endl << "4 : 0.5 de damping sans gravité" << std::endl << "choix :";
		std:: cin >> entry;
	}

	switch (entry) {
	case '1' :
		myWorld.addParticle(Particle(2, 0.9, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		all_gen.push_back(&gravityGenerator);
		all_gen.push_back(&floatingGenerator);
		myWorld.setInput(arrowKeyEffect);
		break;
	case '2' :
		myWorld.addParticle(Particle(1, 1, Vector3D(250, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(1, 1, Vector3D(-250, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.setInput(stringControl);
		break;
	case '3':
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(30, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(-30, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, -30), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, 30), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.setInput(stringControl);
		break;
	}


	
	myWorld.start();

	myMainLoop.execute();

	return 0;
}
