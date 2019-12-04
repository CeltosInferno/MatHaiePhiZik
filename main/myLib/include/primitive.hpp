#ifndef PRIMITIVE
#define PRIMITIVE

#include "rigidBody.hpp"

namespace m_engine {

	class Primitive {

	public :

		Primitive(RigidBody *body);

	private :
		RigidBody* rigidBody;
	};
}





#endif /* PRIMITIVE */
