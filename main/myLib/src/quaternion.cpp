#include "quaternion.hpp"
#include <complex.h>
using namespace m_engine;

//constructors
//instanciating each parameter
Quaternion::Quaternion(double w, double x, double y, double z) : 
	w(w), n(Vector3D(x, y, z)) 
{}
//creating quaternion with an angle and a normal
Quaternion::Quaternion(double theta, Vector3D n) : 
	w(cos(theta / 2)), 
	n(Vector3D((n.x* sin(theta / 2)), (n.y* sin(theta / 2)), (n.z* sin(theta / 2)))) 
{}

//destructor
Quaternion::~Quaternion() {}

Quaternion& Quaternion::operator/=(const double k) {
	w /= k;
	n.x /= k;
	n.y /= k;
	n.z /= k;
	return *this;
}

//log for quaternion
Quaternion Quaternion::Qlog() const {
	double new_w = log(norm());
	Vector3D new_n = n.norm() * acos(w / norm());
	return Quaternion(new_w, new_n.x, new_n.y, new_n.z);
}

Quaternion Quaternion::Qexp() const {
	double new_w = exp(w) * cos(n.norm());
	Vector3D new_n = (exp(w)*sin(n.norm())/n.norm()) * n;
	return Quaternion(new_w, new_n.x, new_n.y, new_n.z);
}

Quaternion Quaternion::Qexp(double t) const {
	Quaternion Qresult = Qlog();
	Qresult = Qresult.dot(t);
	return Qresult.Qexp();
}


Quaternion Quaternion::operator*(const Quaternion& q) const{
	double new_w = w * q.w - n.scalar(q.n);
	Vector3D new_n = w * q.n + q.w * n + n.cross(q.n);
	return Quaternion(new_w, new_n.x, new_n.y, new_n.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	w = w * q.w - n.scalar(q.n);
	n = w * q.n + q.w * n + n.cross(q.n);
	return *this;
}
