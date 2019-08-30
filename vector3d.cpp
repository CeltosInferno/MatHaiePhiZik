#include "vector3d.hpp"
#include <iostream>

using namespace m_engine;

Vector3D::Vector3D(double x=0, double y=0, double z=0) {
	this->coord[0] = x;
	this->coord[1] = y;
	this->coord[2] = z;
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