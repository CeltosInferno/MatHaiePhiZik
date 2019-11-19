#ifndef MATRIX4
#define MATRIX4

#include "vector3d.hpp"
#include "matrix3.hpp"

namespace m_engine {

	/*
		Represents a Matrix 3x4 (which is used as a Matrix 4x4
		with the last line being 0,0,0,1

		Can be used for affine operations with Vector3 
		(as a Vector4 = (vec3, 1))
	*/
	class Matrix4 {
	public:
		//constructor, return the Identity Matrix by default
		Matrix4(double a = 1, double b = 0, double c = 0, double d = 0, 
				double e = 0, double f = 1, double g = 0, double h = 0, 
				double i = 0, double j = 0, double k = 1, double l = 0);
		//creates a Matrix 3x4 matrix, with left being a Matrix 3x3 and right being a Vector3D
		Matrix4(const Matrix3& M, const Vector3D& v);
		//creates a translation Matrix (translation defined by argument)
		Matrix4(const Vector3D& v);

		~Matrix4() {};

		static const Matrix4 Identity;

		//GETTER
		//Access coordinate 'i' by writing vector[i]
		//Return 0 if i outbounded
		double operator[] (int i) const;

		//SETTER
		//Writing coordinate 'i' by writing vector[i]
		//Return vector[0] if i outbounded
		double& operator[] (int i);

		inline double operator() (int i, int j) const {
			return (*this)[i * 4 + j];
		}

		inline double& operator() (int i, int j) {
			return (*this)[i * 4 + j];
		}

		//OPERATORS OVERRIDE
		//Additions operators
		inline Matrix4 operator+(const Matrix4& u) const {
			return Matrix4(data[0] + u[0],
						data[1] + u[1],
						data[2] + u[2],
						data[3] + u[3],
						data[4] + u[4],
						data[5] + u[5],
						data[6] + u[6],
						data[7] + u[7],
						data[8] + u[8],
						data[9] + u[9],
						data[10] + u[10],
						data[11] + u[11]);
		}
		Matrix4& operator+=(const Matrix4& u);

		//Substraction operators
		inline Matrix4 operator-() const { return (*this) * (-1); }
		inline Matrix4 operator-(const Matrix4& u) const {
			return Matrix4(data[0] - u[0],
				data[1] - u[1],
				data[2] - u[2],
				data[3] - u[3],
				data[4] - u[4],
				data[5] - u[5],
				data[6] - u[6],
				data[7] - u[7],
				data[8] - u[8],
				data[9] - u[9],
				data[10] - u[10],
				data[11] - u[11]);
		}
		Matrix4& operator-=(const Matrix4& u);

		//Multiplication with a scalar operators
		inline Matrix4 operator*(double k) const {
			return Matrix4(data[0] * k,
				data[1] * k,
				data[2] * k,
				data[3] * k,
				data[4] * k,
				data[5] * k,
				data[6] * k,
				data[7] * k,
				data[8] * k,
				data[9] * k,
				data[10] * k,
				data[11] * k);
		}
		Matrix4& operator*=(double k);

		//Division by a scalar operators
		inline Matrix4 operator/(double k) const {
			return Matrix4(data[0] / k,
				data[1] / k,
				data[2] / k,
				data[3] / k,
				data[4] / k,
				data[5] / k,
				data[6] / k,
				data[7] / k,
				data[8] / k,
				data[9] / k,
				data[10] / k,
				data[11] / k);
		}
		Matrix4& operator/=(double k);

		//Equality operators
		bool operator==(const Matrix4& u) const;
		inline bool operator!=(const Matrix4& u) const {
			return !(*this == u);
		}

		//Multiplication with an other Matrix3
		Matrix4 operator*(const Matrix4& M) const;
		Matrix4& operator*=(const Matrix4& M);

		//Multiplication with a Vector3D
		Vector3D operator*(const Vector3D& v) const;

		//Multiplication with a Vector3Dconsidered infinitly far
		Vector3D infinityFarMul(const Vector3D& v) const;

		//calcul of the determinent
		double det() const;

		//return the inverse of the matrix, if it exists
		Matrix4 inverse() const;


		inline static Matrix4 TranslationOf(Vector3D tr) {
			return Matrix4(1,0,0,tr.x,
							0,1,0,tr.y,
							0,0,1,tr.z);
		}

		inline static Matrix4 ScaleOf(Vector3D scale) {
			return Matrix4(scale.x,0,0,0,
							0,scale.y,0,0,
							0,0,scale.z,0);
		}
	private:

		double data[12];

	};

	inline Matrix4 operator* (double k, const Matrix4& M) {
		return M * k;
	}

	//Overiding << for printing
	std::ostream& operator<<(std::ostream& os, const Matrix4& M);
	
	inline double det(const Matrix4& M) {
		return M.det();
	}
	inline Matrix4 inverse(const Matrix4& M) {
		return M.inverse();
	}
}

#endif

