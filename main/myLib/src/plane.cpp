#include "plane.hpp"
#include <cmath>

using namespace m_engine;

//Create a plane alonga normale with an offset
Plane::Plane(double offset, const Vector3D& normal) : 
	Primitive(nullptr) , offset(offset) {
	this->normal = normal.normalize();
}

//return if the plane is colliding with a rectangular area centered in middle point with his half dimensions stored in dim
bool Plane::isInArea(const Vector3D& middlePoint, const Vector3D& dim) {
	Vector3D A = offset * normal;
	double planeDist = normal.scalar(middlePoint - A);

	//radius of the sphere representing the area
	double radiusArea = dim.norm();
	
	return (std::abs(planeDist) < radiusArea);
}