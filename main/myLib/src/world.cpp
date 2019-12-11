#include "world.hpp"
#include "vector3d.hpp"
#include <iostream>
#include "octree.hpp"
#include "NarrowSpace.hpp"

#define LINES 10
#define COLUMNS 20

using namespace m_engine;

World::World() : renderer(GraphicRenderer(800, 600, "My World")) {
	
};

World::~World() {

}

//Start the world
void World::start() {
	renderer.OnKeyEvent(ArrowKeyEffect);
}

//Setinput in window
void World::setInput(std::function<void(std::string)> f) {
	ArrowKeyEffect = f;
}

//Add a particle in the world
void World::addParticle(const Particle& part) {
	particles.push_back(part);
}

//Add a rigidBody in the world
void World::addRigidBody(const RigidBody& rb) {
	rigidbodies.push_back(rb);
}

//Add a Plane in the world
void World::addPlane(const Plane& plane) {
	planes.push_back(plane);
}


//Update all the particles of the world
void World::update(double time) {
	//std::cout << "time " << time << std::endl;
	forceRegister.applyForces(time);
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].integrate(time);
		particles[i].cleanAccum();
	}
	for (unsigned int i = 0; i < rigidbodies.size(); i++) {
		rigidbodies[i].integrate(time);
		rigidbodies[i].cleanAccum();
	}
	forceRegister.clear();


	collisionDetected = false;
	//check for collision between particles
	contactResolver.resolveCollisions(time, particles);

	//check for collision between primitives
	//Creating the tree
	Octree tree = Octree(4, Vector3D(), Vector3D(15, 15, 15));
	CollisionData Data;

	
	//insert all colliding items in tree
	int i;
	for(i=0;i<planes.size();i++){
		tree.insert(&planes[i]);
	}
	for(i=0; i<rigidbodies.size();i++)
	{
		tree.insert(&Primitive(&rigidbodies[i]));
	}

	//storing potential collisions
	std::vector<std::pair<Primitive*, Primitive*>> potentialCollisions = tree.resolveTree();

	//solve the contact of potentialCollisions
	for  (std::pair<Primitive*,Primitive*>& potential : potentialCollisions)
	{
		collisionDetected = NarrowSpace::solveContact(potential.first, potential.second, &Data) || collisionDetected;
	}

	//Display collision data
	if (collisionDetected) {
		for (Contact& con : Data.contacts)
		{
			std::cout << "ContactPoint : " << con.contactPoint << std::endl;
			std::cout << "Contact Normale : " << con.contactNormal << std::endl;
			std::cout << "Penetration : " << con.penetration << std::endl;
			std::cout << "-----------------------------" << std::endl;
		}
	}
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
	return renderer.renderCubes(rigidbodies, particles);
}