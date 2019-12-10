#ifndef RIGIDBODY
#define RIGIDBODY

#include "primitive.hpp"
#include "vector3d.hpp"

namespace m_engine {

	class Plane : public Primitive {

	public :
		Plane(double offset, Vector3D normal);
		~Plane() {};

		virtual bool isInArea(Vector3D middlePoint, Vector3D dim);

	private :
		double offset;

		//the normal of the plane (normalized)
		Vector3D normal;



	};
}