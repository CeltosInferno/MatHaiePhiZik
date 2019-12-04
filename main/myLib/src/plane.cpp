#include "plane.hpp"

using namespace m_engine;

Plane::Plane(double offset, Vector3D normal) : offset(offset) {
	this->normal = normal.normalize();
}


bool Plane::isInArea(Vector3D middlePoint, Vector3D dim) {
	Vector3D A = k * normal;
	double planeDist = normal.scalar(middlePoint - A);

	//radius of the sphere representing the area
	double radiusArea = sqrt((dim[0]) * (dim[0]) + (dim[1]) * (dim[1]) + (dim[2]) * (dim[2]));
	
	if (planeDist < radiusArea) return true;

	return false;
}