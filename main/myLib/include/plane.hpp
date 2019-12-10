#ifndef PLANE
#define PLANE

#include "primitive.hpp"
#include "vector3d.hpp"

namespace m_engine {

	class Plane : public Primitive {

	public :
		Plane(double offset, Vector3D normal);
		~Plane() {};

		virtual bool isInArea(Vector3D middlePoint, Vector3D dim);

		inline Vector3D getNormal() { return normal; };
		inline double getOffset() { return offset; };
	private :
		double offset;

		//the normal of the plane (normalized)
		Vector3D normal;

	};
}
#endif