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
		Quaternion(double theta, Vector3D n);
		//destructor
		~Quaternion();
		

		//scaling quaternions methods  with doubles
		//operator *
		inline Quaternion operator*(double k) const {
			return Quaternion(w * k, n.x * k, n.y * k, n.z * k);
		}
		//operator/
		inline Quaternion operator/(double k) const {
			return Quaternion(w / k, n.x / k, n.y / k, n.z / k);
		}
		Quaternion& operator/=(double k);


		//Quaternion exponentiation operators
		//log
		Quaternion Qlog() const;
		//exp
		Quaternion Qexp() const;
		Quaternion Qexp(double t) const;


		//operations methods between quaternions


		//scalar product between two quaternions
		double scalar(const Quaternion& q) const;

		//quaternion multiplication
		Quaternion operator*(const Quaternion& q) const;
		Quaternion& operator*=(const Quaternion& q);

		//return the difference between two quaternions
		Quaternion diff(const Quaternion& b) const;

		//operator-
		inline Quaternion operator-() const {
			return Quaternion(-w, -n.x, -n.y, -n.z);
		}


		//Methods on one quaternion
		//Return the norm
		inline double norm() const {
			return sqrt(w * w + n.sqrNorm());
		};

		//Return the square of the norm
		inline double sqrNorm() const {
			return (w * w + n.sqrNorm());
		};

		
		Quaternion normalize() const {
			double normie = norm();
			return Quaternion(w/normie, n.x/normie, n.y/normie, n.z/normie);
		}

		//conjugate
		inline Quaternion conjugate() const {
			return Quaternion(w, -n.x, -n.y, -n.z);
		}
		//inverse
		inline Quaternion inverse() const {
			return conjugate()/ (sqrNorm());
		}


		double w;
		Vector3D n;

	//private:
	};

	//STATIC OPERATORS
	//Overiding << for printing
	inline std::ostream& operator<<(std::ostream& os, const Quaternion& u) {
		os << "[" << u.w << " " << u.n << "]";
		return os;
	}

	
	inline Quaternion Qlog(const Quaternion& q){
		return q.Qlog();
	}
	
	inline Quaternion Qexp(const Quaternion& q) {
		return q.Qexp();
	}

	inline Quaternion Qexp(const Quaternion& q, double t) {
		return q.Qexp(t);
	}

	inline double scalar(const Quaternion& q1, const Quaternion& q2) {
		return q1.scalar(q2);
	}

	inline Quaternion diff(const Quaternion& q1, const Quaternion& q2) {
		return q1.diff(q2);
	}

	inline double norm(const Quaternion& q) {
		return q.norm();
	}

	inline Quaternion normalize(const Quaternion& q) {
		return q.normalize();
	}

	inline Quaternion conjugate(const Quaternion& q) {
		return q.conjugate();
	}

	inline Quaternion inverse(const Quaternion& q) {
		return q.inverse();
	}
}


#endif /* QUATERNION */