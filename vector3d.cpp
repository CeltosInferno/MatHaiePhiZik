#include "vector3d.hpp"
#include <iostream>

#include "cmath"

using namespace m_engine;

Vector3D::Vector3D(double x, double y, double z) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

Vector3D::~Vector3D() {
}

//GETTER
double Vector3D::operator[](int i) const {
	if (i >= 0 && i <= 2) {
		return coord[i];
	}
	else {
		std::cerr << "Dude, on est en 3D arrête d'être dans le turfu " << i << std::endl;
		return 0;
	}
}

//SETTER
double& Vector3D::operator[](int i) {
	return coord[i];
}


//OPERATORS (A DEFINIR)

Vector3D Vector3D::operator+(const Vector3D& u) const { //TODO
  return Vector3D();
}

Vector3D& Vector3D::operator+=(const Vector3D& u) { //TODO
  return *this;
}

Vector3D Vector3D::operator-(const Vector3D& u) const { //TODO
  return Vector3D(); 
}

Vector3D& Vector3D::operator-=(const Vector3D& u) { //TODO
  return *this;
}

Vector3D Vector3D::operator*(double k) const { //TODO
  return Vector3D();
}

Vector3D& Vector3D::operator*=(double k) { //TODO
  return *this;
}

Vector3D Vector3D::operator*(const Vector3D& u) const { //TODO
  return Vector3D();
}

Vector3D& Vector3D::operator*=(const Vector3D& u) { //TODO
  return *this;
}

bool Vector3D::operator==(const Vector3D& u) const { //TODO
  return true;
}

bool Vector3D::operator!=(const Vector3D& u) const {
  return !(*this == u);
}

Vector3D::operator std::string() const {
	std::string text = "";
	text.append("x : ");
	text.append(std::to_string(coord[0]));
	text.append(" ; y : ");
	text.append(std::to_string(coord[1]));
	text.append(" ; z : ");
	text.append(std::to_string(coord[2]));
	return text;
}

//fonctions

double Vector3D::distance(const Vector3D& u) const {
	return (*this - u).norm();
}

double Vector3D::tripleProduct(const Vector3D& u, const Vector3D& v) const {
	return scalar(u.cross(v));
}

double Vector3D::scalar(const Vector3D& u) const {
	double scal = 0;
	for (int i = 0; i < 3; i++) {
		scal += coord[i] * coord[i];
	}
	return scal;
}

double Vector3D::norm() const {
  /*
	double s = 0;
	for (int i = 0; i < 3; i++){
		s += coord[i] * coord[i];
		}*/
	return std::sqrt(scalar(*this));
}

Vector3D Vector3D::normalize() const {
	double n = norm();
	if (n == 0) return Vector3D();
	Vector3D normVec(coord[0] / n, coord[1] / n, coord[2] / n);
	return normVec;
}

Vector3D Vector3D::cross(const Vector3D& u) const { //TODO
  return Vector3D();
}


/* Methodes statiques */

Vector3D operator* (double k, const Vector3D& v) {
  return v*k;
}

double scalar(const Vector3D& v, const Vector3D& u) {
  return v.scalar(u);
}

double norm(const Vector3D& v) {
  return v.norm();
}

Vector3D normalize(const Vector3D& v) {
  return v.normalize();
}

Vector3D cross(const Vector3D& v, const Vector3D& u) {
  return v.cross(u);
}

double distance(const Vector3D& v, const Vector3D& u) {
  return v.distance(u);
}

double tripleProduct(const Vector3D& v1,
		     const Vector3D& v2,
		     const Vector3D& v3) {
  return v1.tripleProduct(v2, v3);
}
