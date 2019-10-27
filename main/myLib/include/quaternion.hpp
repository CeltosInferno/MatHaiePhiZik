#ifndef QUATERNION
#define QUATERNION

#include "vector3d.hpp"

namespace m_engine {

	class Quaternion {
	public:
		//constuctors
		//instanciating each parameter
		Quaternion(double w = 0, double x = 0, double y = 0, double z = 0);
		//instanciating with an angle and a normal vector
		Quaternion(double theta = 0, Vector3D n = Vector3D());
		//destructor
		~Quaternion();
		

		//scaling quaternions methods  with doubles
		//operator dot
		inline Quaternion dot(const double k) const {
			return Quaternion(w * k, n.x * k, n.y * k, n.z * k);
		}
		//operator/
		inline Quaternion operator/(const double k) const {
			return Quaternion(w / k, n.x / k, n.y / k, n.z / k);
		}
		Quaternion& operator/=(const double k);

		//log
		Quaternion Qlog() const;
		//exp
		Quaternion Qexp() const;
		Quaternion Qexp(double t) const;

		//scalar product
		double scalar(const Quaternion q) const;

		//operations methods between quaternions

		//quaternion multiplication
		Quaternion operator*(const Quaternion q) const;
		Quaternion& operator*=(const Quaternion q);

		Quaternion diff(const Quaternion b) const;

		//operator-
		inline Quaternion operator-() const {
			return Quaternion(-w, -n.x, -n.y, -n.z);
		}


		//Return the norm
		double norm() const;

		//Return the square of the norm
		double sqrNorm() const;

		//conjugate
		inline Quaternion conjugate() const {
			return Quaternion(w, -n.x, -n.y, -n.z);
		}
		//inverse
		inline Quaternion inverse() const {
			return conjugate()/norm();
		}


		double w;
		Vector3D n;

	private:
	};

	//STATIC OPERATORS
	//Overiding << for printing
	inline std::ostream& operator<<(std::ostream& os, const Quaternion& u) {
		os << "[" << u.w << " " << u.n << "]";
		return os;
	}

	inline Quaternion operator* (const Quaternion q1, const Quaternion q2) {
		return q1 * q2;
	}
}


#endif /* QUATERNION */