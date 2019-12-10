#include "primitive.hpp"

using namespace m_engine;

Primitive::Primitive(RigidBody* body) : rigidBody(body) {

}

// tells whether the primitive is in the area or not, described by the point in the middle and the dimensions of the area
bool Primitive::isInArea(const Vector3D& middlePoint, const Vector3D& dim) {
	if (rigidBody != nullptr) {
		//radius of the sphere representing the body
		double radiusBody = Vector3D(rigidBody->dx, rigidBody->dy, rigidBody->dz).norm()/2;

		//radius of the sphere representing the area
		double radiusArea = dim.norm();

		double dist = (middlePoint - rigidBody->getPos()).norm();

		//if the spheres intersect
		return (dist < radiusBody + radiusArea);
	}
	return false;
}

