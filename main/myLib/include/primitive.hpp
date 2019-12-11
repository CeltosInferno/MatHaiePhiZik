#ifndef PRIMITIVE
#define PRIMITIVE

#include "rigidBody.hpp"

namespace m_engine {

	//This class represent an object that can collide
	class Primitive {

	public :

		Primitive(RigidBody* body = nullptr);
		~Primitive() {};

		//this function return the address of the stored rigidbodie if existing
		inline RigidBody* getRigidBody() const { return rigidBody; }

		// tells whether the primitive is in the area or not, described by the point in the middle and the dimensions of the area
		virtual bool isInArea(const Vector3D& middlePoint, const Vector3D& dim);

		//return if the primitive is a rigidbody
		inline bool isRigidBody() { return rigidBody != nullptr; }

		//this method can be used to change the addr of the rigidbody the primitive is pointing at
		inline void setAddr(RigidBody* addr) { rigidBody = addr; }
	private :

		// Rigidbody pointer, null if it is a plan
		RigidBody* rigidBody;
	};
}

#endif /* PRIMITIVE */
