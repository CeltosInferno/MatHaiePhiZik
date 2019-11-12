#include "matrix4.hpp"

using namespace m_engine;

Matrix4::Matrix4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l) {
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	data[4] = e;
	data[5] = f;
	data[6] = g;
	data[7] = h;
	data[8] = i;
	data[9] = j;
	data[10] = k;
	data[11] = l;
}

const Matrix4 Matrix4::Identity;

//GETTER
double Matrix4::operator[](int i) const {
	if (i >= 0 && i < 12) {
		return data[i];
	}
	else {
		std::cerr << "Error : can only acces to a dimension between 0 and 11, tried : " << i << std::endl;
		return -1;
	}
}

//SETTER
double& Matrix4::operator[](int i) {
	if (i >= 0 && i < 12) {
		return data[i];
	}
	else {
		std::cerr << "Error : can only acces to a dimension between 0 and 11, tried : " << i << std::endl;
		return data[0];
	}
}

//Storing the addition of two vectors
Matrix4& Matrix4::operator+=(const Matrix4& u) {
	for (int i = 0; i < 12; i++) {
		data[i] += u[i];
	}
	return *this;
}

//Storing the substraction of two vectors
Matrix4& Matrix4::operator-=(const Matrix4& u) {
	for (int i = 0; i < 12; i++) {
		data[i] -= u[i];
	}
	return *this;
}

//Storing the multiplication with a scalar
Matrix4& Matrix4::operator*=(double k) {
	for (int i = 0; i < 12; i++) {
		data[i] *= k;
	}
	return *this;
}

//Storing the division with a scalar
Matrix4& Matrix4::operator/=(double k) {
	for (int i = 0; i < 12; i++) {
		data[i] /= k;
	}
	return *this;
}

//Multiplication with an other Matrix4
Matrix4 Matrix4::operator*(const Matrix4& M) const {
	return Matrix4(data[0] * M[0] + data[1] * M[4] + data[2] * M[8],
		data[0] * M[1] + data[1] * M[5] + data[2] * M[9],
		data[0] * M[2] + data[1] * M[6] + data[2] * M[10],
		data[0] * M[3] + data[1] * M[7] + data[2] * M[11] + data[3],
		data[4] * M[0] + data[5] * M[4] + data[6] * M[8],
		data[4] * M[1] + data[5] * M[5] + data[6] * M[9],
		data[4] * M[2] + data[5] * M[6] + data[6] * M[10],
		data[4] * M[3] + data[5] * M[7] + data[6] * M[11] + data[7],
		data[8] * M[0] + data[9] * M[4] + data[10] * M[8],
		data[8] * M[1] + data[9] * M[5] + data[10] * M[9],
		data[8] * M[2] + data[9] * M[6] + data[10] * M[10],
		data[8] * M[3] + data[9] * M[7] + data[10] * M[11] + data[11]
	);
}

Matrix4& Matrix4::operator*=(const Matrix4& M) {

	double aux[12];

	aux[0] = data[0] * M[0] + data[1] * M[4] + data[2] * M[8];
	aux[1] = data[0] * M[1] + data[1] * M[5] + data[2] * M[9];
	aux[2] = data[0] * M[2] + data[1] * M[6] + data[2] * M[10];
	aux[3] = data[0] * M[3] + data[1] * M[7] + data[2] * M[11] + data[3];
	aux[4] = data[4] * M[0] + data[5] * M[4] + data[6] * M[8];
	aux[5] = data[4] * M[1] + data[5] * M[5] + data[6] * M[9];
	aux[6] = data[4] * M[2] + data[5] * M[6] + data[6] * M[10];
	aux[7] = data[4] * M[3] + data[5] * M[7] + data[6] * M[11] + data[7];
	aux[8] = data[8] * M[0] + data[9] * M[4] + data[10] * M[8];
	aux[9] = data[8] * M[1] + data[9] * M[5] + data[10] * M[9];
	aux[10] = data[8] * M[2] + data[9] * M[6] + data[10] * M[10];
	aux[11] = data[8] * M[3] + data[9] * M[7] + data[10] * M[11] + data[11];

	for (int i = 0; i < 12; i++) {
		data[i] = aux[i];
	}

	return (*this);
}


//Multiplication with a Vector3D
Vector3D Matrix4::operator*(const Vector3D& v) const {
	return Vector3D(data[0] * v[0] + data[1] * v[1] + data[2] * v[2] + data[3],
		data[4] * v[0] + data[5] * v[1] + data[6] * v[2] + data[7],
		data[8] * v[0] + data[9] * v[1] + data[10] * v[2] + data[11]
	);
}

//Multiplication with a Vector3D considered infinity far
Vector3D Matrix4::infinityFarMul(const Vector3D& v) const {
	return Vector3D(data[0] * v[0] + data[1] * v[1] + data[2] * v[2],
		data[4] * v[0] + data[5] * v[1] + data[6] * v[2],
		data[8] * v[0] + data[9] * v[1] + data[10] * v[2]
	);
}


//calcul of the det
double Matrix4::det() const {
	return data[0] * data[5] * data[10]
		+ data[4] * data[9] * data[2]
		+ data[8] * data[1] * data[6]
		- data[0] * data[9] * data[6]
		- data[8] * data[5] * data[2]
		- data[4] * data[1] * data[10];
}


Matrix4 Matrix4::inverse() const {
	double det = this->det();
	if (det != 0) {
		return Matrix4(data[5] * data[10] - data[6] * data[9],
			data[2] * data[9] - data[1] * data[10],
			data[1] * data[6] - data[2] * data[5],

			data[1] * data[7] * data[10] +
			data[2] * data[5] * data[11] +
			data[3] * data[6] * data[9] -
			data[1] * data[6] * data[11] -
			data[2] * data[7] * data[9] -
			data[3] * data[5] * data[10],

			data[6] * data[8] - data[4] * data[10],
			data[0] * data[10] - data[2] * data[8],
			data[2] * data[4] - data[0] * data[6],

			data[0] * data[6] * data[11] +
			data[4] * data[10] * data[3] +
			data[8] * data[2] * data[7] -
			data[0] * data[7] * data[10] -
			data[2] * data[4] * data[11] -
			data[8] * data[6] * data[3],

			data[4] * data[9] - data[5] * data[8],
			data[1] * data[8] - data[0] * data[9],
			data[0] * data[5] - data[1] * data[4],

			data[0] * data[7] * data[9] +
			data[1] * data[4] * data[11] +
			data[3] * data[5] * data[8] -
			data[0] * data[5] * data[11] -
			data[3] * data[4] * data[9] -
			data[1] * data[7] * data[8]

		) / det;
	}
	else {
		std::cerr << "Error : the det of the matrix is 0, there is no inverse" << std::endl;
		return -1;
	}
}

std::ostream& m_engine::operator<<(std::ostream& os, const Matrix4& M) {
	os << "[";
	for (int i = 0; i < 12; i++) {
		os << M[i];
		if (i < 11) {
			os << ",";
			if (i % 4 == 3) os << std::endl << " ";
		}
	}
	os << "]";
	return os;
}

