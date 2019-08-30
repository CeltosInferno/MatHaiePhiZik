#include "vector3d.hpp"
#include <iostream>

#include "cmath"

using namespace m_engine;

Vector3D::Vector3D(double x = 0, double y = 0, double z = 0) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

Vector3D::~Vector3D() {
}

//GETTER
double Vector3D::operator[](int i) const {
	if (i >= 0 && i <= 2) {
		return this->coord[i];
	}
	else {
		std::cerr << "Dude, on est en 3D arrête d'être dans le turfu " << i << std::endl;
		return 0;
	}
};

//SETTER
double& Vector3D::operator[](int i) {
	return this->coord[i];
};


double Vector3D::distance(const Vector3D& u) const {
	return (*this-u).norm();
};
double Vector3D::tripleProduct(const Vector3D& u, const Vector3D& v) const {
	return this->scalar(u.cross(v));
};


double Vector3D::norm() const {
	double s = 0;
	for (double x : coord){
		s += x * x;
	}

	return std::sqrt(s);
}

Vector3D Vector3D::normalize() const {
	double norm = this->norm();
	Vector3D normVec(coord[0] / norm, coord[1] / norm, coord[2] / norm);
	return normVec;
}
