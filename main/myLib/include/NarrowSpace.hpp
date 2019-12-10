#ifndef NARROW_SPACE
#define NARROW_SPACE

#include "vector3d.hpp"
#include "rigidBody.hpp"
#include <vector>

#include "plane.hpp"
#include "primitive.hpp"

namespace m_engine {



	struct Contact {
		Contact(RigidBody* rb, const Vector3D& contactPoint, const Vector3D& contactNormal, float penetration):
			rb(rb), contactPoint(contactPoint), 
			contactNormal(contactNormal), penetration(penetration)
		{}

		RigidBody* rb; //the object containing the contactPoint
		Vector3D contactPoint; //the point where the collision occurs
		Vector3D contactNormal; //the vector of collision (oriented toward rb in order to use a force)
		float penetration; //the degree of prenetration
	};

	struct CollisionData {
		std::vector<Contact> contacts; //a list of contacts
		inline void addContact(const Contact& c) {
			contacts.push_back(c);
		}
	};

	class NarrowSpace {
	public:
		//given two objects, will return if there is a collision (in narrow space) and stores it in Collision Data
		static bool solveContact(Primitive*, Primitive*, CollisionData*);
	private:
		static bool solveContact(RigidBody*, RigidBody*, CollisionData*);
		static bool solveContact(RigidBody*, const Plane*, CollisionData*);
	};



}

#endif /*NARROW_SPACE*/