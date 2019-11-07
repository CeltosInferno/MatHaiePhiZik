#ifndef QUATERNION
#define QUATERNION

#include "vector3d.hpp"
#include "matrix3.hpp"

namespace m_engine {

	class Quaternion {
	public:
		//constuctors
		//instanciating each parameter
		Quaternion(double w = 0, double x = 0, double y = 0, double z = 0);
		//instanciating with w and the imaginary part as a vector
		Quaternion(double w, Vector3D v);
		//destructor
		~Quaternion();

		//generate a quaternion from the axis angle defined by angle and axe of rotation
		//angle must be given in rad
		inline static Quaternion FormAxisAngle(double theta, Vector3D n) {
			return Quaternion(cos(theta / 2), n * sin(theta / 2));
		}

		inline static Quaternion Identity() {
			return Quaternion(1, 0, 0, 0);
		}
		

		//scaling quaternions methods  with doubles
		//operator *
		inline Quaternion operator*(double k) const {
			return Quaternion(w * k, n * k);
		}
		Quaternion& operator*=(double k);
		//operator/
		inline Quaternion operator/(double k) const {
			return Quaternion(w / k, n / k);
		}
		Quaternion& operator/=(double k);


		//Quaternion exponentiation operators
		//return log(q)
		Quaternion Qlog() const;
		//return exp(q)
		Quaternion Qexp() const;
		//return q^t
		Quaternion Qexp(double t) const;
		//because it is possible : return this^q
		Quaternion Qexp(const Quaternion& q) const;


		//operations methods between quaternions
		inline bool operator==(const Quaternion& q) const {
			return (w==q.w && n == q.n);
		}
		inline bool operator!=(const Quaternion& q) const {
			return !(w == q.w && n == q.n);
		}
		//scalar product between two quaternions
		double scalar(const Quaternion& q) const;

		//quaternion multiplication
		Quaternion operator*(const Quaternion& q) const;
		Quaternion& operator*=(const Quaternion& q);

		//return the difference between two quaternions
		Quaternion diff(const Quaternion& b) const;

		//operator-
		inline Quaternion operator-() const {
			return Quaternion(-w, -n);
		}
		
		//sum of quaternions : not very useful for rotations
		inline Quaternion operator+(const Quaternion& q) const {
			return Quaternion(w+q.w, n+q.n);
		}
		Quaternion& operator+=(const Quaternion& q);

		//diff of quaternions : not useful for rotations
		inline Quaternion operator-(const Quaternion& q) const {
			return Quaternion(w - q.w, n-q.n);
		}
		Quaternion& operator-=(const Quaternion& q);

		//Methods on one quaternion
		//Return the norm
		inline double norm() const {
			return sqrt(w * w + n.sqrNorm());
		};

		//Return the square of the norm
		inline double sqrNorm() const {
			return (w * w + n.sqrNorm());
		};

		
		inline Quaternion normalize() const {
			if (w == 0 && n.x == 0 && n.y == 0 && n.z == 0)
				return *this;
			else
				return  *this / norm();
		}

		//return true if the quaternion is a rotation (ie norm = 1)
		bool isNormalized() const;

		//conjugate
		inline Quaternion conjugate() const {
			return Quaternion(w, -n);
		}
		//inverse
		inline Quaternion inverse() const {
			return conjugate()/ (sqrNorm());
		}

		inline Matrix

		double w;
		Vector3D n;
		
	};

	//STATIC OPERATORS
	//Overiding << for printing
	inline std::ostream& operator<<(std::ostream& os, const Quaternion& u) {
		os << "[" << u.w << " " << u.n << "]";
		return os;
	}

	//in order to write k*q instead of only q*k
	inline Quaternion operator*(double k, const Quaternion& q) {
		return q*k;
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

	inline bool isNormalized(const Quaternion& q) {
		return q.isNormalized();
	}

	inline bool equal(const Quaternion& q1, const Quaternion& q2) {
		return q1 == q2;
	}

	inline bool not_equal(const Quaternion& q1, const Quaternion& q2) {
		return !(q1 == q2);
	}
}


#endif /* QUATERNION */