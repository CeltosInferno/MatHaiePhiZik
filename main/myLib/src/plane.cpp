#include "plane.hpp"
#include <cmath>

using namespace m_engine;

Plane::Plane(double offset, const Vector3D& normal) : 
	Primitive(nullptr) , offset(offset) {
	this->normal = normal.normalize();
}


bool Plane::isInArea(const Vector3D& middlePoint, const Vector3D& dim) {
	Vector3D A = offset * normal;
	double planeDist = normal.scalar(middlePoint - A);

	//radius of the sphere representing the area
	double radiusArea = dim.norm();
	//autre manière de faire : sqrt((dim[0]) * (dim[0]) + (dim[1]) * (dim[1]) + (dim[2]) * (dim[2]));
	
	return (std::abs(planeDist) < radiusArea);
}