#include "vector3d.hpp"

using namespace m_engine;

Vector3D::Vector3D() {
}

Vector3D::~Vector3D() {
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
