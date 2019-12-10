#ifndef PRIMITIVE
#define PRIMITIVE

#include "rigidBody.hpp"

namespace m_engine {

	class Primitive {

	public :

		Primitive(RigidBody* body = nullptr);
		~Primitive() {};

		inline RigidBody* getRigidBody() const { return rigidBody; }

		// tells whether the primitive is in the area or not, described by the point in the middle and the dimensions of the area
		virtual bool isInArea(const Vector3D& middlePoint, const Vector3D& dim);

		inline bool isRigidBody() { return rigidBody != nullptr; }

	private :

		// Rigidbody pointer, null if it is a plan
		RigidBody* rigidBody;
	};
}

#endif /* PRIMITIVE */
