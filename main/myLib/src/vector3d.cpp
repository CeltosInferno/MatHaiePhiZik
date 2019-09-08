#include "vector3d.hpp"
#include <iostream>

#include <cmath>

using namespace m_engine;

Vector3D::Vector3D(double x, double y, double z): x(x), y(y), z(z) {}

Vector3D::~Vector3D() {}

//GETTER
double Vector3D::operator[](int i) const {
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		std::cerr << "Error : can only acces to a dimension between 0 and 2, tried : " << i << std::endl;
		return -1;
	}
}	

//SETTER
double& Vector3D::operator[](int i) {
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		std::cerr << "Error : can only acces to a dimension between 0 and 2, tried : " << i << std::endl;
		return x;
	}
}


//OPERATORS

//Storing the addition of two vectors
Vector3D& Vector3D::operator+=(const Vector3D& u) {
  x += u.x;
  y += u.y;
  z += u.z;
  return *this;
}

//Storing the substraction of two vectors
Vector3D& Vector3D::operator-=(const Vector3D& u) {
  x -= u.x;
  y -= u.y;
  z -= u.z;
  return *this;
}

//Storing the multiplication with a scalar
Vector3D& Vector3D::operator*=(double k) {
  x *= k;
  y *= k;
  z *= k;
  return *this;
}

//Storing the multiplication of each m_coordinate of two vectors
Vector3D& Vector3D::operator*=(const Vector3D& u) {
  x *= u.x;
  y *= u.y;
  z *= u.z;
  return *this;
}

Vector3D& Vector3D::operator/=(double k) {
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

//FUNCTIONS

//Return distance between two points
double Vector3D::distance(const Vector3D& u) const {
  return (*this - u).norm();
}

//Return the volume of a Parallelepiped defined by trhee vectors
double Vector3D::tripleProduct(const Vector3D& u, const Vector3D& v) const {
  return this->scalar(u.cross(v));
}

//Return the scalar product of two vectors
double Vector3D::scalar(const Vector3D& u) const {
	return (x * u.x + y * u.y + z * u.z);
}

//Return the norm of the vector
double Vector3D::norm() const {
  return std::sqrt(sqrNorm());
}

//Return the square of the norm of the vector
double Vector3D::sqrNorm() const {
	return scalar(*this);
}

//Return the vector normalized
Vector3D Vector3D::normalize() const {
  double n = norm();
  if (n == 0) return Vector3D();
  return (*this / n);
}

//Return the wedge product of two vectors
Vector3D Vector3D::cross(const Vector3D& u) const {
  return Vector3D(y*u.z - z*u.y, z*u.x - x*u.z, x*u.y - y*u.x);
}
