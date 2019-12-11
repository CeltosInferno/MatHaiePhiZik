#include "narrowSpace.hpp"

using namespace m_engine;

/*
	represent a 3D rectangle based on a rigidBody
*/
class Box {
public:
	Vector3D vertices[8];
	Box(const RigidBody& rb) {
		const Vector3D& pos = rb.getPos();
		double x = rb.dx;
		double y = rb.dy;
		double z = rb.dz;
		for (int i = 0; i < 8; ++i) {
			vertices[i] = pos + Vector3D(convert(x,i/4), 
										convert(y, (i/2)%2), 
										convert(z, i % 2));
		}
	};

private:
	//return the opposite of x according to boolean value of i
	static inline double convert(double x, int i) {
		return (i == 0) ? x : -x;
	}
};

bool NarrowSpace::solveContact(Primitive* p1, Primitive* p2, CollisionData* collData) {
	Plane* plane1 = dynamic_cast<Plane*>(p1);
	RigidBody* rb1 = p1->getRigidBody();

	Plane* plane2 = dynamic_cast<Plane*>(p2);
	RigidBody* rb2 = p2->getRigidBody();

	//the first 
	if (rb1 == nullptr && rb2 == nullptr) {
		//no collision handled as there are no rigidBodies
		return false;
	}
	if (rb2 == nullptr && plane2 != nullptr) {
		//rigidBody1 + Plane2
		return solveContact(rb1, plane2, collData);
	}
	if (rb1 == nullptr && plane1 != nullptr) {
		//rigidBody2 + Plane1
		return solveContact(rb2, plane1, collData);
	}
	if (rb1 && rb2) {
		//rigidBody2 + rigidBody1
		return solveContact(rb1, rb2, collData);
	}
	//should not happen : only if the rb are null but the object is not a plane
	return false;
};

bool NarrowSpace::solveContact(RigidBody* rb1, RigidBody* rb2, CollisionData* collData) {
	//we check how the 2 objects are colliding and where they are from
	Vector3D n((rb1->getPos() - rb2->getPos()).normalize());
	double va = rb1->getVel().scalar(n);
	double vb = rb2->getVel().scalar(n);
	double vs = va - vb;

	Box box1(*rb1);
	Box box2(*rb2);
	return false;
}

bool NarrowSpace::solveContact(RigidBody* rb, const Plane* p, CollisionData* collData) {
	Box box(*rb);
	bool isCollided = false;
	for (const Vector3D& vertice : box.vertices) {
		double dist = vertice.scalar(p->getNormal());
		if (dist < p->getOffset()) { //if the vertex is below the plane
			collData->addContact(Contact(rb, vertice, p->getNormal(), dist));
			isCollided = true;
		}
	}
	return isCollided;
}