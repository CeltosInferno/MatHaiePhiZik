#include "matrix3.hpp"

using namespace m_engine;

Matrix3::Matrix3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	data[4] = e;
	data[5] = f;
	data[6] = g;
	data[7] = h;
	data[8] = i;
}


//GETTER
double Matrix3::operator[](int i) const {
	if (i >= 0 && i < 9) {
		return data[i];
	} else {
		std::cerr << "Error : can only acces to a dimension between 0 and 8, tried : " << i << std::endl;
		return -1;
	}
}

//SETTER
double& Matrix3::operator[](int i) {
	if (i >= 0 && i < 9) {
		return data[i];
	}
	else {
		std::cerr << "Error : can only acces to a dimension between 0 and 8, tried : " << i << std::endl;
		return data[0];
	}
}


//Storing the addition of two vectors
Matrix3& Matrix3::operator+=(const Matrix3& u) {
	for (int i = 0; i < 9; i++) {
		data[i] += u[i];
	}
	return *this;
}

//Storing the substraction of two vectors
Matrix3& Matrix3::operator-=(const Matrix3& u) {
	for (int i = 0; i < 9; i++) {
		data[i] -= u[i];
	}
	return *this;
}

//Storing the multiplication with a scalar
Matrix3& Matrix3::operator*=(double k) {
	for (int i = 0; i < 9; i++) {
		data[i] *= k;
	}
	return *this;
}

Matrix3& Matrix3::operator/=(double k) {
	for (int i = 0; i < 9; i++) {
		data[i] /= k;
	}
	return *this;
}

//Multiplication with an other Matrix3
Matrix3 Matrix3::operator*(const Matrix3& M) const {
	return Matrix3(data[0] * M[0] + data[1] * M[3] + data[2] * M[6],
					data[0] * M[1] + data[1] * M[4] + data[2] * M[7],
					data[0] * M[2] + data[1] * M[5] + data[2] * M[8],
					data[3] * M[0] + data[4] * M[3] + data[5] * M[6],
					data[3] * M[1] + data[4] * M[4] + data[5] * M[7],
					data[3] * M[2] + data[4] * M[5] + data[5] * M[8],
					data[6] * M[0] + data[7] * M[3] + data[8] * M[6],
					data[6] * M[1] + data[7] * M[4] + data[8] * M[7],
					data[6] * M[2] + data[7] * M[5] + data[8] * M[8]
					);
}

Matrix3& Matrix3::operator*=(const Matrix3& M) {

	double aux[9];

	aux[0] = data[0] * M[0] + data[1] * M[3] + data[2] * M[6];
	aux[1] = data[0] * M[1] + data[1] * M[4] + data[2] * M[7];
	aux[2] = data[0] * M[2] + data[1] * M[5] + data[2] * M[8];
	aux[3] = data[3] * M[0] + data[4] * M[3] + data[5] * M[6];
	aux[4] = data[3] * M[1] + data[4] * M[4] + data[5] * M[7];
	aux[5] = data[3] * M[2] + data[4] * M[5] + data[5] * M[8];
	aux[6] = data[6] * M[0] + data[7] * M[3] + data[8] * M[6];
	aux[7] = data[6] * M[1] + data[7] * M[4] + data[8] * M[7];
	aux[8] = data[6] * M[2] + data[7] * M[5] + data[8] * M[8];
	
	for (int i = 0; i < 9; i++) {
		data[i] = aux[i];
	}

	return (*this);
}

//Multiplication with a Vector3D
Vector3D Matrix3::operator*(const Vector3D& v) const {
	return Vector3D(data[0] * v[0] + data[1] * v[1] + data[2] * v[2],
					data[3] * v[0] + data[4] * v[1] + data[5] * v[2],
					data[6] * v[0] + data[7] * v[1] + data[8] * v[2]
					);
}


//calcul of the det
double Matrix3::det() const {
	return data[0] * data[4] * data[8]
		+ data[3] * data[7] * data[2]
		+ data[6] * data[1] * data[5]
		- data[0] * data[7] * data[5]
		- data[6] * data[4] * data[2]
		- data[3] * data[1] * data[8];
}

Matrix3 Matrix3::inverse() const {
	double det = this->det();
	if (det != 0) {
		return Matrix3(data[4] * data[8] - data[5] * data[7],
			data[2] * data[7] - data[1] * data[8],
			data[1] * data[5] - data[2] * data[4],
			data[5] * data[6] - data[3] * data[8],
			data[0] * data[8] - data[2] * data[6],
			data[2] * data[3] - data[0] * data[5],
			data[3] * data[7] - data[4] * data[6],
			data[1] * data[6] - data[0] * data[7],
			data[0] * data[4] - data[1] * data[3]
			) / det;
	}
	else {
		std::cerr << "Error : the det of the matrix is 0, there is no inverse" << std::endl;
		return -1;
	}
}


//return the transposed of the matrix
Matrix3 Matrix3::t() const {
	return Matrix3(data[0], data[3], data[6], data[1], data[4], data[7], data[2], data[5], data[8]);
}

std::ostream& operator<<(std::ostream& os, const Matrix3& M) {
	os << "[ ";
	for (int i = 0; i < 9; i++) {
		os << M[i];
		if (i < 8) {
			os << ",";
			if (i%3 == 2) os << std::endl;
		}
	}
	os << "]";
	return os;
}