#include "vector3d.hpp"

#include "cmath"

using namespace m_engine;

Vector3D::Vector3D(double x = 0, double y = 0, double z = 0) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

Vector3D::~Vector3D() {
}




double Vector3D::norm() const {
	double s = 0;
	for (double x : coord)
	{
		s += x * x;
	}

	return std::sqrt(s);
}

Vector3D Vector3D::normalize() const {
	double norm = this->norm();
	Vector3D normVec(coord[0] / norm, coord[1] / norm, coord[2] / norm);
	return normVec;
}
