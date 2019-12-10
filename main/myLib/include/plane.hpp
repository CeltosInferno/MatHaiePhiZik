#ifndef PLANE
#define PLANE

#include "primitive.hpp"
#include "vector3d.hpp"

namespace m_engine {

	class Plane : public Primitive {

	public :
		Plane(double offset, const Vector3D& normal);
		~Plane() {};

		/*
			Return if a rectangle centered arround middlePoint
			might collide with this plane 
			by axproximating it as a sphere of radius norm(dim)
		*/
		virtual bool isInArea(const Vector3D& middlePoint, const Vector3D& dim);

		inline const Vector3D& getNormal() const { return normal; };
		inline double getOffset() const { return offset; };
	private :
		double offset;

		//the normal of the plane (normalized)
		Vector3D normal;



	};
}
#endif