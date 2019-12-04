#include "primitive.hpp"

using namespace m_engine;

Primitive::Primitive(RigidBody* body) : rigidBody(body) {

}

// tells whether the primitive is in the area or not, described by the point in the middle and the dimensions of the area
bool Primitive::isInArea(Vector3D middlePoint, Vector3D dim) {
	if (rigidBody) {
		//radius of the sphere representing the body
		double radiusBody = sqrt((rigidBody->dx) * (rigidBody->dx) + (rigidBody->dy) * (rigidBody->dy) + (rigidBody->dz) * (rigidBody->dz));

		//radius of the sphere representing the area
		double radiusArea = sqrt((dim[0]) * (dim[0]) + (dim[1]) * (dim[1]) + (dim[2]) * (dim[2]));

		//if the spheres intersect
		if (middlePoint.distance(rigidBody->getPos()) < radiusBody + radiusArea) return true;

		return false;
	}
	return false;
}