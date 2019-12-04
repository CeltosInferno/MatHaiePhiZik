#ifndef PRIMITIVE
#define PRIMITIVE

#include "rigidBody.hpp"

namespace m_engine {

	class Primitive {

	public :

		Primitive(RigidBody* body);
		~Primitive() {};

		// tells whether the primitive is in the area or not, described by the point in the middle and the dimensions of the area
		virtual bool isInArea(Vector3D middlePoint, Vector3D dim);

	private :

		// Rigidbody pointer, null if it is a plan
		RigidBody* rigidBody;
	};
}

#endif /* PRIMITIVE */
