#include "quaternion.hpp"

using namespace m_engine;

//constructors
//instanciating each parameter
Quaternion::Quaternion(double w, double x, double y, double z) : 
	w(w), n(x, y, z) 
{}
//creating quaternion with w and v as a vector
Quaternion::Quaternion(double w, Vector3D v) :
	w(w), n(v)
{}

//destructor
Quaternion::~Quaternion() {}

Quaternion& Quaternion::operator*=(double k) {
	w *= k;
	n *= k;
	return *this;
}

Quaternion& Quaternion::operator/=(double k) {
	w /= k;
	n /= k;
	return *this;
}

//log for quaternion
Quaternion Quaternion::Qlog() const {
	double new_w = log(norm());
	//if n = 0, should be 0
	Vector3D new_n = n.normalize() * acos(w / n.norm());
	return Quaternion(new_w, new_n);
}

Quaternion Quaternion::Qexp() const {
	double new_w = exp(w) * cos(n.norm());
	Vector3D new_n = (exp(w)*sin(n.norm()))*n.normalize();
	return Quaternion(new_w, new_n);
}

Quaternion Quaternion::Qexp(double t) const {
	Quaternion Qresult = Qlog();
	Qresult *= t;
	return Qresult.Qexp();
}

Quaternion Quaternion::Qexp(const Quaternion& q) const {
	Quaternion Qresult = Qlog();
	Qresult *= q;
	return Qresult.Qexp();
}

//scalar product
double Quaternion::scalar(const Quaternion& q) const {
	return ((w * q.w) + (n.scalar(q.n)));
};


//Multiplication of two quaternions
Quaternion Quaternion::operator*(const Quaternion& q) const{
	double new_w = w * q.w - n.scalar(q.n);
	Vector3D new_n = w * q.n + q.w * n + n.cross(q.n);
	return Quaternion(new_w, new_n);
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	w = w * q.w - n.scalar(q.n);
	n = w * q.n + q.w * n + n.cross(q.n);
	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& q) {
	w += q.w;
	n += q.n;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q) {
	w -= q.w;
	n -= q.n;
	return *this;
}

//return the difference between two quaternions
Quaternion Quaternion::diff(const Quaternion& b) const {
	return b * inverse();
};

bool Quaternion::isNormalized() const {
	//TODO
	return (abs(norm() - 1) < 0.000000000000001);
}
