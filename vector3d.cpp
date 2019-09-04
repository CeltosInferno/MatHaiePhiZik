#include "vector3d.hpp"
#include <iostream>

#include <cmath>

using namespace m_engine;

Vector3D::Vector3D(double x, double y, double z) {
  m_coord[0] = x;
  m_coord[1] = y;
  m_coord[2] = z;
}

Vector3D::~Vector3D() {
}

//GETTER
double Vector3D::operator[](int i) const {
  if (i >= 0 && i <= 2) {
    return m_coord[i];
  }
  else {
    std::cerr << "Error : can't acces to a dimension over 3 or below 0" << i << std::endl;
    return 0;
  }
}

//SETTER
double& Vector3D::operator[](int i) {
	if (i >= 0 && i <= 2) {
		return m_coord[i];
	}
	else {
		std::cerr << "Error : can't acces to a dimension over 3 or below 0 " << i << std::endl;
		return m_coord[0];
	}
}


//OPERATORS

//Adding two vectors
Vector3D Vector3D::operator+(const Vector3D& u) const {	
  return Vector3D(m_coord[0]+u[0], m_coord[1] + u[1], m_coord[2] + u[2]);
}

//Storing the addition of two vectors
Vector3D& Vector3D::operator+=(const Vector3D& u) {
  m_coord[0] += u[0];
  m_coord[1] += u[1];
  m_coord[2] += u[2];
  return *this;
}

//Substract two vectors
Vector3D Vector3D::operator-(const Vector3D& u) const {
  return Vector3D(m_coord[0] - u[0], m_coord[1] - u[1], m_coord[2] - u[2]);
}

//Storing the substraction of two vectors
Vector3D& Vector3D::operator-=(const Vector3D& u) {
  m_coord[0] -= u[0];
  m_coord[1] -= u[1];
  m_coord[2] -= u[2];
  return *this;
}

//Multiplication with a scalar
Vector3D Vector3D::operator*(double k) const {
  return Vector3D(m_coord[0]*k, m_coord[1]*k, m_coord[2]*k);
}

//Storing the multiplication with a scalar
Vector3D& Vector3D::operator*=(double k) {
  m_coord[0] *= k;
  m_coord[1] *= k;
  m_coord[2] *= k;
  return *this;
}

//Multiply each m_coordinate of two vectors
Vector3D Vector3D::operator*(const Vector3D& u) const {
  return Vector3D(m_coord[0] * u[0], m_coord[1] * u[1], m_coord[2] * u[2]);
}

//Storing the multiplication of each m_coordinate of two vectors
Vector3D& Vector3D::operator*=(const Vector3D& u) {
  m_coord[0] *= u[0];
  m_coord[1] *= u[1];
  m_coord[2] *= u[2];
  return *this;
}

//True if two vectors are equals
bool Vector3D::operator==(const Vector3D& u) const {
  bool res = true;
  int i = 0;
  while (res == true && i < 3 && m_coord[i] == u[i]) {
    i++;
  }
  return res;
}

//True if two vectors are not equals
bool Vector3D::operator!=(const Vector3D& u) const {
  return !(*this == u);
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
  double scal = 0;
  for (int i = 0; i < 3; i++) {
    scal += m_coord[i] * u[i];
  }
  return scal;
}

//Return the norm of the vector
double Vector3D::norm() const {
  return std::sqrt(scalar(*this));
}

//Return the square of the norm of the vector
double Vector3D::sqrNorm() const {
	return scalar(*this);
}

//Return the vector normalized
Vector3D Vector3D::normalize() const {
  double n = norm();
  if (n == 0) return Vector3D();
  Vector3D normVec(m_coord[0] / n, m_coord[1] / n, m_coord[2] / n);
  return normVec;
}

//Return the wedge product of two vectors
Vector3D Vector3D::cross(const Vector3D& u) const {
  return Vector3D(m_coord[1]*u[2] - m_coord[2]*u[1], m_coord[2]*u[0] - m_coord[0]*u[2], m_coord[0]*u[1] - m_coord[1]*u[0]);
}


