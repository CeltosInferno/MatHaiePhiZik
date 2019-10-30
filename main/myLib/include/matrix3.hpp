#ifndef MATRIX3
#define MATRIX3

#include "vector3d.hpp"

namespace m_engine {

	class Matrix3 {
	public:
		//Renvoie la matrice identité par défaut
		Matrix3(double a = 1, double b = 0, double c = 0, double d = 0, double e = 1, double f = 0, double g = 0, double h = 0, double i = 1);
		~Matrix3() {};

		//GETTER
		//Access coordinate 'i' by writing vector[i]
		//Return 0 if i outbounded
		double operator[] (int i) const;

		//SETTER
		//Writing coordinate 'i' by writing vector[i]
		//Return vector[0] if i outbounded
		double& operator[] (int i);

		//OPERATORS OVERRIDE
		//Additions operators
		inline Matrix3 operator+(const Matrix3& u) const {
			return Matrix3(data[0] + u[0], data[1] + u[1], data[2] + u[2], data[3] + u[3], data[4] + u[4], data[5] + u[5], data[6] + u[6], data[7] + u[7], data[8] + u[8]);
		}
		Matrix3& operator+=(const Matrix3& u);

		//Substraction operators
		inline Matrix3 operator-() const { return (*this) * (-1); }
		inline Matrix3 operator-(const Matrix3& u) const {
			return Matrix3(data[0] - u[0], data[1] - u[1], data[2] - u[2], data[3] - u[3], data[4] - u[4], data[5] - u[5], data[6] - u[6], data[7] - u[7], data[8] - u[8]);
		}
		Matrix3& operator-=(const Matrix3& u);

		//Multiplication with a scalar operators
		inline Matrix3 operator*(double k) const {
			return Matrix3(data[0] * k, data[1] * k, data[2] * k, data[3] * k, data[4] * k, data[5] * k, data[6] * k, data[7] * k, data[8] * k);
		}
		Matrix3& operator*=(double k);

		//Division by a scalar operators
		inline Matrix3 operator/(double k) const {
			return Matrix3(data[0] / k, data[1] / k, data[2] / k, data[3] / k, data[4] / k, data[5] / k, data[6] / k, data[7] / k, data[8] / k);
		}
		Matrix3& operator/=(double k);

		//Equality operators
		inline bool operator==(const Matrix3& u) const {
			bool res = true;
			for (int i = 0; i < 9; i++) {
				res &= data[i] == u[i];
			}
			return res;
		}
		inline bool operator!=(const Matrix3& u) const {
			return !(*this == u);
		}

		//Multiplication with an other Matrix3
		Matrix3 operator*(const Matrix3& M) const;
		Matrix3& operator*=(const Matrix3& M);

		//Multiplication with a Vector3D
		Vector3D operator*(const Vector3D& v) const;

		//calcul af the det
		double det() const;

		//return the inverse of the matrix, if it exists
		Matrix3 inverse() const;

		//return the transposed of the matrix
		Matrix3 t() const;

	private:

		double data[9];

	};
}

#endif
