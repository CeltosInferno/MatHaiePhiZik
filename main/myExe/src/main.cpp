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


//This function can be bind with the graphic renderer to assign what to do whith each arrow
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


//This function can be bind with the graphic renderer to assign what to do whith each arrow
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


//This function define what to do for the Basic String demonstration
void string_case() {
	static ParticleString bouncingString1(myWorld.particles[1], 0.5, 490);
	static ParticleString bouncingString2(myWorld.particles[0], 0.5, 490);
	myWorld.forceRegister.add(&myWorld.particles[0], &bouncingString1);
	myWorld.forceRegister.add(&myWorld.particles[1], &bouncingString2);
}

//This function define what to do for the Blob demonstration
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


//This function will be bind with the main loop and will be executed at the beginning of each frame
bool onStartLoop(double time, int id_iteration) {

	switch (entry) {
		//Case of float demonstratino
		case '1':
			for (ParticleForceGenerator* g : all_gen) {
				for (Particle& p : myWorld.particles) {
					myWorld.forceRegister.add(&p, g);
				}
			}
			break;
		//case of string demonstration
		case'2':
			string_case();
			break;
		//case of blob demonstration
		case '3':
			blob_case();
			break;
		//case of collision demonstration
		case '4':
			for (ParticleForceGenerator* g : all_gen) {
				for (Particle& p : myWorld.particles) {
					myWorld.forceRegister.add(&p, g);
				}
			}
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


	static ParticleGravityGenerator gravityGenerator(Vector3D(0, 0, -_G));
	static ParticleFloatingGenerator floatingGenerator(10, 100, 0);
	
	int ressort_dumping = 1;

	//Displaying in a terminal the demonstrations options
	while (entry!= '0' && entry != '1' && entry != '2' 
		&& entry != '3' && entry != '4')
	{
		std::cout << "choisissez une démonstration" << std::endl
			<< "0 : Quitter" << std::endl
			<< "1 : Floating Generator avec gravité" << std::endl 
			<< "2 : Deux particules avec ressort" << std::endl 
			<< "3 : Blob" << std::endl 
			<< "4 : Test de collision avec le sol" << std::endl
			<< "choix :";
		std:: cin >> entry;
	}

	switch (entry) {
	//Floating demonstration
	case '1' :
		myMainLoop.setZoom(8);
		//setting up particles
		myWorld.addParticle(Particle(2, 0.9, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		//recording force generators
		all_gen.push_back(&gravityGenerator);
		all_gen.push_back(&floatingGenerator);
		//setting up input's reaction
		myWorld.setInput(arrowKeyEffect);
		break;
	//String demonstration
	case '2' :
		//Setting up particles
		myWorld.addParticle(Particle(1, 1, Vector3D(250, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(1, 1, Vector3D(-250, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		//setting up input's reaction
		myWorld.setInput(stringControl);
		break;
	//Blob demonstration
	case '3':
		//Setting up particles
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(30, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(-30, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, -30), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		myWorld.addParticle(Particle(3, ressort_dumping, Vector3D(0, 0, 30), Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
		//Setting up input's reaction
		myWorld.setInput(stringControl);
		break;
	case '4':
		myMainLoop.setZoom(15);
		//add particules with a radius
		myWorld.addParticle(Particle(10, ressort_dumping, Vector3D(-1, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 1));
		myWorld.addParticle(Particle(10, ressort_dumping, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 1));
		//recording force generators
		//all_gen.push_back(&gravityGenerator);
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
