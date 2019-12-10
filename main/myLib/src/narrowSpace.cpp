#include "narrowSpace.hpp"

using namespace m_engine;

class Box {
public:
	Vector3D vertices[8];
	Box(const RigidBody& rb) {
		const Vector3D& pos = rb.getPos();
		double x = rb.dx;
		double y = rb.dy;
		double z = rb.dz;
		//triple boucle for sinon mais relou
		vertices[0] = pos + Vector3D(x, y, z);
		vertices[1] = pos + Vector3D(x, y, -z);
		vertices[2] = pos + Vector3D(x, -y, z);
		vertices[3] = pos + Vector3D(x, -y, -z);
		vertices[4] = pos + Vector3D(-x, y, z);
		vertices[5] = pos + Vector3D(-x, y, -z);
		vertices[6] = pos + Vector3D(-x, -y, z);
		vertices[7] = pos + Vector3D(-x, -y, -z);
	};
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
		//rigidBody2 + Plane1
		return solveContact(rb1, rb2, collData);
	}
	//should not happen : only if the rb are null but the object is not a plane
	return false;
};

bool NarrowSpace::solveContact(RigidBody* rb1, RigidBody* rb2, CollisionData* collData) {
	return false;
}

bool NarrowSpace::solveContact(RigidBody* rb, Plane* p, CollisionData* collData) {
	Box box(*rb);
	bool isCollided = false;
	for (const Vector3D& vertice : box.vertices) {
		double dist = vertice.scalar(p->getNormal());
		if (dist < 0) {
			collData->addContact(Contact(rb, vertice, p->getNormal(), dist));
			isCollided = true;
		}
	}
	return isCollided;
}