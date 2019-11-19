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


//rotate the quaternion according to v
void Quaternion::rotateByVector(const Vector3D& v) {
	Quaternion new_result = *this *Quaternion(0, v.x, v.y, v.z);
	w = new_result.w;
	n = new_result.n;
}

//Update angular velocity
void Quaternion::updateAngularVelocity(const Vector3D& v, double deltat) {
	*this = *this + (deltat/2 * Quaternion(0, v) * (*this)) ;
}

//log for quaternion
Quaternion Quaternion::Qlog() const {
	double new_w = log(norm());
	//if n = 0, should be 0
	Vector3D new_n = n.normalize() * acos(w / norm());
	return Quaternion(new_w, new_n);
}

Quaternion Quaternion::Qexp() const {
	double new_w = exp(w) * cos(n.norm());
	Vector3D new_n = (exp(w)*sin(n.norm()))*n.normalize();
	return Quaternion(new_w, new_n);
}

Quaternion Quaternion::Qexp(double t) const {
	if (norm() == 0) { return *this; }
	Quaternion Qresult = Qlog();
	Qresult *= t;
	return Qresult.Qexp();
}

Quaternion Quaternion::Qexp(const Quaternion& q) const {
	if (norm() == 0) { return *this; }
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
	double new_w = w * q.w - n.scalar(q.n);
	Vector3D new_n = w * q.n + q.w * n + n.cross(q.n);
	w = new_w;
	n = new_n;
	return *this;
}

//Addition of two quaternions
Quaternion& Quaternion::operator+=(const Quaternion& q) {
	w += q.w;
	n += q.n;
	return *this;
}

//Substraction of two quaternions
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

Matrix3 Quaternion::toMatrix3() const{
	double x=n.x;
	double y=n.y;
	double z=n.z;
	double a=1 - (2*y*y  +  2*z*z);
	double b=2*x*y + 2*z*w;
	double c=2*x*z - 2*y*w;

	double d=2*x*y - 2*z*w;
	double e=1 - (2*x*x + 2*z*z);
	double f=2*y*z + 2*x*w;

	double g=2*x*z + 2*y*w;
	double h=2*y*z - 2*x*w;
	double i=1- (2*x*x + 2*y*y);

	return Matrix3(
		a,b,c,
		d,e,f,
		g,h,i
	);
}

Matrix4 Quaternion::toMatrix4() const{
	double x=n.x;
	double y=n.y;
	double z=n.z;
	double a=1 - (2*y*y  +  2*z*z);
	double b=2*x*y + 2*z*w;
	double c=2*x*z - 2*y*w;

	double d=2*x*y - 2*z*w;
	double e=1 - (2*x*x + 2*z*z);
	double f=2*y*z + 2*x*w;

	double g=2*x*z + 2*y*w;
	double h=2*y*z - 2*x*w;
	double i=1- (2*x*x + 2*y*y);

	return Matrix4(
		a, b, c, x,
		d,e,f, y,
		g,h,i, z
	);
}