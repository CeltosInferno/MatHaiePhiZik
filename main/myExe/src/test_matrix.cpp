#include <cassert>
#include <iostream>

#include "matrix3.hpp"
#include "matrix4.hpp"

#define EPSILON 1e-10

using namespace m_engine;
using namespace std;

//test de l'instanciation et l'affectation
void test_m3_start();
//test de l'egalite ou difference
void test_m3_equality();
//test l'operation +, +=
void test_m3_add();
//test l'operation a-b, a-=b et -a
void test_m3_sub();
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m3_mult();
//testb l'operation *, *=, entre matrices
void test_m3_mult2();
//testb l'operation *, *=, entre matrices et vecteurs
void test_m3_mult3();
//test de det
void test_m3_det();
//test de inverse
void test_m3_inverse();
//test de t
void test_m3_transpose();

//test de l'instanciation et l'affectation
void test_m4_start();
//test de l'egalite ou difference
void test_m4_equality();
//test l'operation +, +=
void test_m4_add();
//test l'operation a-b, a-=b et -a
void test_m4_sub();
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m4_mult();
//testb l'operation *, *=, entre matrices
void test_m4_mult2();
//testb l'operation *, *=, entre matrices et vecteurs
void test_m4_mult3();
//test de det
void test_m4_det();
//test de inverse
void test_m4_inverse();

void testMatrix3() {
	cout << "test of Matrix3:" << endl;
	test_m3_start();
	test_m3_equality();
	test_m3_add();
	test_m3_sub();
	test_m3_mult();
	test_m3_mult2();
	test_m3_mult3();
	test_m3_det();
	test_m3_inverse();
	test_m3_transpose();
	cout << "test of Matrix3 OK" << endl;
}

void testMatrix4() {
	cout << "test of Matrix4:" << endl;
	test_m4_start();
	test_m4_equality();
	test_m4_add();
	test_m4_sub();
	test_m4_mult();
	test_m4_mult2();
	test_m4_mult3();
	test_m4_det();
	test_m4_inverse();
	cout << "test of Matrix4 OK" << endl;
}

int main() {
	cout << "\ntest_matrix:" << endl;
	cout << "--------------------" << endl;
	testMatrix3();
	cout << "--------------------" << endl;
	testMatrix4();
	cout << "test_matrix OK" << endl;
	return 0;
}

inline bool cmp_double(double a, double b) {
	return abs(a - b) < EPSILON;
}

/* ========================================================== 
						Matrix3
   ========================================================== */

void cmp_m3_data(const Matrix3& M, const double data[9]) {
	for (int i = 0; i < 9; i++) {
		assert(cmp_double(M[i], data[i]));
	}
}

Matrix3 init_m3_data(const double data[9]) {
	return Matrix3(data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7], data[8]);
}

void display_data(const double data[9]) {
	for (int i = 0; i < 9; i++) {
		cout << data[i] << ", ";
	}
	cout << endl;
}

#define DATA_M3 6

static double m3_data[DATA_M3][9] = {
	{1,0,0,
	0,1,0,
	0,0,1},

	{1,2,3,4,5,6,7,8,9},

	{1,2,-3,
	4,-5,6,
	7,-8,9},
	
	{1,0,3,
	0,1,2,
	1,-1,1},

	{1,0,3,
	0,-0.5,2,
	0.5,-1,1},

	{0,0,0,0,0,0,0,0,0}
};

#define DATA_V3 5

static Vector3D v3_data[DATA_V3] = {
	Vector3D(1,0,0),
	Vector3D(1,2,3),
	Vector3D(1,2,-3),
	Vector3D(1,0,3.5),
	Vector3D(0,0,0)
};

//test de l'instanciation et l'affectation
void test_m3_start() {
	cout << "test_m3_start" << flush;
	//On verifie les valeurs de la matrice identité
	cmp_m3_data(Matrix3::Identity, m3_data[0]);
	cout << "." << flush;

	for (int i = 0; i < DATA_M3; ++i) {
		Matrix3 M = init_m3_data(m3_data[i]);
		cmp_m3_data(M, m3_data[i]);
		cout << "." << flush;

		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				assert(M[j * 3 + k] == M(j, k));
		cout << "." << flush;
	}
	
	cout << ".OK" << endl;
}

//test de l'egalite ou difference
void test_m3_equality() {
	cout << "test_m3_equality" << flush;
	//On verifie les valeurs de la matrice identité
	assert(Matrix3::Identity == init_m3_data(m3_data[0]));
	cout << "." << flush;

	for (int i = 0; i < DATA_M3; ++i) {
		Matrix3 M = init_m3_data(m3_data[i]);
		for (int j = 0; j < DATA_M3; ++j) {
			Matrix3 M2 = init_m3_data(m3_data[j]);
			if (j == i) {
				assert(M == M2);
				assert(M2 == M);
				assert(!(M != M2));
				assert(!(M2 != M));
			}
			else {
				assert(M != M2);
				assert(M2 != M);
				assert(!(M == M2));
				assert(!(M2 == M));
			}
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

static double m3_add_data[3][DATA_M3][9] = {
	{
		{2,0,0,
		0,2,0,
		0,0,2},

		{2,2,3,4,6,6,7,8,10},

		{2,2,-3,
		4,-4,6,
		7,-8,10},

		{2,0,3,
		0,2,2,
		1,-1,2},

		{2,0,3,
		0,0.5,2,
		0.5,-1,2},

		{1,0,0,
		0,1,0,
		0,0,1}
	},
	{
		{2,2,3,4,6,6,7,8,10},
		{2,4,6,8,10,12,14,16,18},
		{2,4,0,8,0,12,14,0,18},
		{2,2,6,4,6,8,8,7,10},
		{2,2,6,4,4.5,8,7.5,7,10},
		{1,2,3,4,5,6,7,8,9}
	},
	{ 
		{1,0,0,
		0,1,0,
		0,0,1},

		{1,2,3,4,5,6,7,8,9},

		{1,2,-3,
		4,-5,6,
		7,-8,9},

		{1,0,3,
		0,1,2,
		1,-1,1},

		{1,0,3,
		0,-0.5,2,
		0.5,-1,1},

		{0,0,0,0,0,0,0,0,0}
	}
};

//test l'operation +, +=
void test_m3_add() {
	cout << "test_m3_add" << flush;

	Matrix3 Minit = Matrix3::Identity;
	for(int i = 0; i < DATA_M3; i++) {
		Matrix3 M = init_m3_data(m3_data[i]);
		Matrix3 M2 = Minit + M;
		cmp_m3_data(M2, m3_add_data[0][i]);
		cout << "." << flush;

		Matrix3 M3 = M + Minit;
		assert(M3 == M2);
		M += Minit;
		assert(M3 == M);
		cout << "." << flush;
	}
	Minit = init_m3_data(m3_data[1]);
	for (int i = 0; i < DATA_M3; i++) {
		Matrix3 M = init_m3_data(m3_data[i]);
		Matrix3 M2 = Minit + M;
		cmp_m3_data(M2, m3_add_data[1][i]);
		cout << "." << flush;

		Matrix3 M3 = M + Minit;
		assert(M3 == M2);
		M += Minit;
		assert(M3 == M);
		cout << "." << flush;
	}
	//vide
	Minit = init_m3_data(m3_data[DATA_M3-1]);
	for (int i = 0; i < DATA_M3; i++) {
		Matrix3 M = init_m3_data(m3_data[i]);
		Matrix3 M2 = Minit + M;
		cmp_m3_data(M2, m3_add_data[2][i]);
		cout << "." << flush;

		Matrix3 M3 = M + Minit;
		assert(M3 == M2);
		M += Minit;
		assert(M3 == M);
		cout << "." << flush;

		assert(M2 == M);
		cout << "." << flush;
	}
	cout << ".OK" << endl;
}
//test l'operation a-b, a-=b et -a
void test_m3_sub() {
	cout << "test_m3_sub" << flush;
	for (int i = 0; i < DATA_M3; i++) {
		Matrix3 M = init_m3_data(m3_data[i]);
		const Matrix3 M2 = -M;
		for (int j = 0; j < 9; j++) {
			assert(cmp_double(M2[j], -(M[j])));
		}
		assert(-M2 == M);
		cout << "." << flush;
		for (int j = 0; j < DATA_M3; j++) {
			Matrix3 M3 = init_m3_data(m3_data[j]);
			Matrix3 M4 = M3 + M2;
			assert(M4 == M3 - M);
			M4 -= M2;
			assert(M4 == M3);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m3_mult() {
	cout << "test_m3_mult" << flush;
	double coef[5] = { 1,0.3,-4,-7.8,0 };
	for (int x = 0; x < DATA_M3; x++) {
		Matrix3 M = init_m3_data(m3_data[x]);
		assert(M + M == 2 * M);
		assert(M + M == M * 2);
		for (int i = 0; i < 5; i++) {
			double k = coef[i];
			Matrix3 M2 = k * M;
			Matrix3 M3 = M * k;
			assert(M2 == M3);
			cout << "." << flush;
			for (int j = 0; j < 9; j++) {
				assert(M[j] * k == M2[j]);
			}
			cout << "." << flush;
			M2 = M;
			M2 *= k;
			assert(M2 == M3);
			cout << "." << flush;
			if (k != 0) {
				M2 /= k;
				assert(M2 == M);
				M3 = M3 / k;
				assert(M3 == M);
				cout << "." << flush;
			}
		}
	}
	cout << ".OK" << endl;
}

void test_mult_assert(const Matrix3& M1, const Matrix3& M2, const Matrix3& Mres) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double res = 0;
			for (int k = 0; k < 3; k++) {
				res += M1(i, k) * M2(k, j);
			}
			assert(res == Mres(i, j));
		}
	}
}

void test_m3_mult2() {
	cout << "test_m3_mult2" << flush;
	for (int x = 0; x < DATA_M3; x++) {
		Matrix3 M1 = init_m3_data(m3_data[x]);
		assert(M1 == M1 * Matrix3::Identity);
		assert(M1 == Matrix3::Identity * M1);
		cout << "." << flush;
		for (int y = 0; y < DATA_M3; y++) {
			Matrix3 M2 = init_m3_data(m3_data[x]);
			test_mult_assert(M1, M2, M1 * M2);
			Matrix3 M3 = M1;
			M3 *= M2;
			assert(M3 == M1 * M2);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

void test_mult_assert(const Matrix3& M1, const Vector3D& v) {
	Vector3D v2 = M1 * v;
	for (int i = 0; i < 3; i++) {
		double res = 0;
		for (int k = 0; k < 3; k++) {
			res += M1(i, k) * v[k];
		}
		assert(cmp_double(res, v2[i]));
	}
}

void test_m3_mult3() {
	cout << "test_m3_mult3" << flush;
	for (int z = 0; z < DATA_V3; z++) {
		const Vector3D& v = v3_data[z];
		for (int x = 0; x < DATA_M3; x++) {
			Matrix3 M1 = init_m3_data(m3_data[x]);
			test_mult_assert(M1, v);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

void test_value_det(const Matrix3& M) {
	double theorical_det = 0;
	for (int i = 0; i < 3; i++) {
		double c1 = 1;
		double c2 = -1;
		for (int j = 0; j < 3; j++) {
			c1 *= M((i + j) % 3, j);
			c2 *= M(j, (3 + i - j) % 3);
		}
		theorical_det += c1 + c2;
	}
	assert(cmp_double(theorical_det, det(M)));
}

//test de det
void test_m3_det() {
	cout << "test_m3_det" << flush;
	assert(cmp_double(Matrix3::Identity.det(), 1));
	cout << "." << flush;
	for (int x = 0; x < DATA_M3; x++) {
		Matrix3 M1 = init_m3_data(m3_data[x]);
		assert(M1.det() == det(M1));
		double coef[5] = { 1,0.3,-4,-7.8,0 };
		for (int i = 0; i < 5; i++) {
			double k = coef[i];
			assert(cmp_double(det(M1 * k), det(M1) * pow(k, 3)));
		}
		cout << "." << flush;
		for (int y = 0; y < DATA_M3; y++) {
			Matrix3 M2 = init_m3_data(m3_data[x]);
			Matrix3 M3 = M1 * M2;
			Matrix3 M4 = M2 * M1;
			assert(cmp_double(det(M3), det(M1) * det(M2)));
			assert(cmp_double(det(M3), det(M4)));
			cout << "." << flush;
		}
		test_value_det(M1);
		cout << "." << flush;
	}
	cout << ".OK" << endl;
}
//test de inverse
void test_m3_inverse() {
	cout << "test_m3_inverse" << flush;
	assert(Matrix3::Identity.inverse() == Matrix3::Identity);
	cout << "." << flush;
	for (int x = 0; x < DATA_M3 - 1; x++) {
		Matrix3 M = init_m3_data(m3_data[x]);
		if(M.det() != 0) {
			Matrix3 M2 = M.inverse();
			assert(cmp_double(det(M2), 1 / det(M)));
			cout << "." << flush;
			assert(M2 == inverse(M));
			assert(M2 * M == M2 * M);
			assert(M2 * M == Matrix3::Identity);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}
//test de t
void test_m3_transpose() {
	cout << "test_m3_transpose" << flush;
	for (int x = 0; x < DATA_M3; x++) {
		Matrix3 M1 = init_m3_data(m3_data[x]);
		Matrix3 M2 = M1.t();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				assert(M2(i, j) == M1(j, i));
		cout << "." << flush;
		for (int y = 0; y < DATA_M3; y++) {
			Matrix3 M3 = init_m3_data(m3_data[x]);
			Matrix3 M4 = M3.t();
			assert((M1 * M3).t() == (M4 * M2));
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

/* ========================================================== 
						Matrix4
   ========================================================== */

void cmp_m4_data(const Matrix4& M, const double data[12]) {
	for (int i = 0; i < 12; i++) {
		assert(cmp_double(M[i], data[i]));
	}
}

Matrix4 init_m4_data(const double data[12]) {
	return Matrix4(data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7],
		data[8], data[9], data[10], data[11]);
}

Matrix3 get_sub_matrix(const Matrix4& M) {
	return Matrix3(M(0, 0), M(0, 1), M(0, 2),
		M(1, 0), M(1, 1), M(1, 2),
		M(2, 0), M(2, 1), M(2, 2));
}

Vector3D get_sub_vector(const Matrix4& M) {
	return Vector3D(M(0, 3), M(1, 3), M(2, 3));
}

#define DATA_M4 6

static double m4_data[DATA_M4][12] = {
	{1,0,0,0,
	0,1,0,0,
	0,0,1,0},

	{1,2,3,4,5,6,7,8,9,10,11,12},

	{1,2,-3,0,
	4,-5,6,-4,
	7,-8,9,0},

	{1,0,3,1,
	0,1,2,1,
	1,-1,1,0.5},

	{1,0,3,0,
	0,-0.5,2,-2,
	0.5,-1,1,1},

	{0,0,0,0,0,0,0,0,0,0,0,0}
};

void test_m4_start() {
	cout << "test_m4_start" << flush;
	//On verifie les valeurs de la matrice identité
	cmp_m4_data(Matrix4::Identity, m4_data[0]);
	cout << "." << flush;

	for (int i = 0; i < DATA_M4; ++i) {
		Matrix4 M = init_m4_data(m4_data[i]);
		cmp_m4_data(M, m4_data[i]);
		cout << "." << flush;

		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 4; k++)
				assert(M[j * 4 + k] == M(j, k));
		cout << "." << flush;
	}

	for (int j = 0; j < DATA_V3; ++j) {
		Matrix4 Mtranslate(v3_data[j]);
		assert(v3_data[j] == get_sub_vector(Mtranslate));
		assert(Matrix3::Identity == get_sub_matrix(Mtranslate));
		cout << "." << flush;
		for (int i = 0; i < DATA_M3; ++i) {
			Matrix3 Minit = init_m3_data(m3_data[i]);
			Matrix4 M(Minit, v3_data[j]);
			assert(Minit == get_sub_matrix(M));
			assert(v3_data[j] == get_sub_vector(M));
			cout << "." << flush;
		}
	}

	cout << ".OK" << endl;
}

//test de l'egalite ou difference
void test_m4_equality() {
	cout << "test_m4_equality" << flush;
	//On verifie les valeurs de la matrice identité
	assert(Matrix4::Identity == init_m4_data(m4_data[0]));
	cout << "." << flush;

	for (int i = 0; i < DATA_M4; ++i) {
		Matrix4 M = init_m4_data(m4_data[i]);
		for (int j = 0; j < DATA_M4; ++j) {
			Matrix4 M2 = init_m4_data(m4_data[j]);
			if (j == i) {
				assert(M == M2);
				assert(M2 == M);
				assert(!(M != M2));
				assert(!(M2 != M));
			}
			else {
				assert(M != M2);
				assert(M2 != M);
				assert(!(M == M2));
				assert(!(M2 == M));
			}
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

static double m4_add_data[4][DATA_M4][12] = {
	{
		{2,0,0,0,
		0,2,0,0,
		0,0,2,0},

		{2,2,3,4,5,7,7,8,9,10,12,12},

		{2,2,-3,0,
		4,-4,6,-4,
		7,-8,10,0},

		{2,0,3,1,
		0,2,2,1,
		1,-1,2,0.5},

		{2,0,3,0,
		0,0.5,2,-2,
		0.5,-1,2,1},

		{1,0,0,0,
		0,1,0,0,
		0,0,1,0}
	},
	{
		{2,2,3,4,5,7,7,8,9,10,12,12},
		{2,4,6,8,10,12,14,16,18,20,22,24},
		{2,4,0,4,9,1,13,4,16,2,20,12},
		{2,2,6,5,
		5,7,9,9,
		10,9,12,12.5},

		{2,2,6,4,
		5,5.5,9,6,
		9.5,9,12,13},
		{1,2,3,4,5,6,7,8,9,10,11,12}
	},
	{
		{1,0,0,0,
		0,1,0,0,
		0,0,1,0},

		{1,2,3,4,5,6,7,8,9,10,11,12},

		{1,2,-3,0,
		4,-5,6,-4,
		7,-8,9,0},

		{1,0,3,1,
		0,1,2,1,
		1,-1,1,0.5},

		{1,0,3,0,
		0,-0.5,2,-2,
		0.5,-1,1,1},

		{0,0,0,0,0,0,0,0,0,0,0,0}
	}
};

//test l'operation +, +=
void test_m4_add() {
	cout << "test_m4_add" << flush;

	Matrix4 Minit = Matrix4::Identity;
	for (int i = 0; i < DATA_M4; i++) {
		Matrix4 M = init_m4_data(m4_data[i]);
		Matrix4 M2 = Minit + M;
		cmp_m4_data(M2, m4_add_data[0][i]);
		cout << "." << flush;

		Matrix4 m4 = M + Minit;
		assert(m4 == M2);
		M += Minit;
		assert(m4 == M);
		cout << "." << flush;
	}
	Minit = init_m4_data(m4_data[1]);
	for (int i = 0; i < DATA_M4; i++) {
		Matrix4 M = init_m4_data(m4_data[i]);
		Matrix4 M2 = Minit + M;
		cmp_m4_data(M2, m4_add_data[1][i]);
		cout << "." << flush;

		Matrix4 m4 = M + Minit;
		assert(m4 == M2);
		M += Minit;
		assert(m4 == M);
		cout << "." << flush;
	}
	//vide
	Minit = init_m4_data(m4_data[DATA_M4 - 1]);
	for (int i = 0; i < DATA_M4; i++) {
		Matrix4 M = init_m4_data(m4_data[i]);
		Matrix4 M2 = Minit + M;
		cmp_m4_data(M2, m4_add_data[2][i]);
		cout << "." << flush;

		Matrix4 m4 = M + Minit;
		assert(m4 == M2);
		M += Minit;
		assert(m4 == M);
		cout << "." << flush;

		assert(M2 == M);
		cout << "." << flush;
	}
	cout << ".OK" << endl;
}
//test l'operation a-b, a-=b et -a
void test_m4_sub() {
	cout << "test_m4_sub" << flush;
	for (int i = 0; i < DATA_M4; i++) {
		Matrix4 M = init_m4_data(m4_data[i]);
		const Matrix4 M2 = -M;
		for (int j = 0; j < 12; j++) {
			assert(cmp_double(M2[j], -(M[j])));
		}
		assert(-M2 == M);
		cout << "." << flush;
		for (int j = 0; j < DATA_M4; j++) {
			Matrix4 m4 = init_m4_data(m4_data[j]);
			Matrix4 M4 = m4 + M2;
			assert(M4 == m4 - M);
			M4 -= M2;
			assert(M4 == m4);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m4_mult() {
	cout << "test_m4_mult" << flush;
	double coef[5] = { 1,0.3,-4,-7.8,0 };
	for (int x = 0; x < DATA_M4; x++) {
		Matrix4 M = init_m4_data(m4_data[x]);
		assert(M + M == 2 * M);
		assert(M + M == M * 2);
		for (int i = 0; i < 5; i++) {
			double k = coef[i];
			Matrix4 M2 = k * M;
			Matrix4 m4 = M * k;
			assert(M2 == m4);
			cout << "." << flush;
			for (int j = 0; j < 12; j++) {
				assert(M[j] * k == M2[j]);
			}
			cout << "." << flush;
			M2 = M;
			M2 *= k;
			assert(M2 == m4);
			cout << "." << flush;
			if (k != 0) {
				M2 /= k;
				assert(M2 == M);
				m4 = m4 / k;
				assert(m4 == M);
				cout << "." << flush;
			}
		}
	}
	cout << ".OK" << endl;
}

void test_mult_assert(const Matrix4& M1, const Matrix4& M2, const Matrix4& Mres) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			double res = 0;
			for (int k = 0; k < 3; k++) {
				res += M1(i, k) * M2(k, j);
			}
			if (j == 3) res += M2(i, 3);
			assert(res == Mres(i, j));
		}
	}
}

void test_m4_mult2() {
	cout << "test_m4_mult2" << flush;
	for (int x = 0; x < DATA_M4; x++) {
		Matrix4 M1 = init_m4_data(m4_data[x]);
		assert(M1 == M1 * Matrix4::Identity);
		assert(M1 == Matrix4::Identity * M1);
		cout << "." << flush;
		for (int y = 0; y < DATA_M4; y++) {
			Matrix4 M2 = init_m4_data(m4_data[x]);
			test_mult_assert(M1, M2, M1 * M2);
			Matrix4 m4 = M1;
			m4 *= M2;
			assert(m4 == M1 * M2);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

void test_mult_assert(const Matrix4& M1, const Vector3D& v) {
	Vector3D v2 = M1 * v;
	for (int i = 0; i < 3; i++) {
		double res = 0;
		for (int k = 0; k < 3; k++) {
			res += M1(i, k) * v[k];
		}
		res += M1(i, 3);
		assert(cmp_double(res, v2[i]));
	}
}

void test_m4_mult3() {
	cout << "test_m4_mult3" << flush;
	for (int z = 0; z < DATA_V3; z++) {
		const Vector3D& v = v3_data[z];
		for (int x = 0; x < DATA_M4; x++) {
			Matrix4 M1 = init_m4_data(m4_data[x]);
			test_mult_assert(M1, v);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}

void test_value_det(const Matrix4& M) {
	double theorical_det = 0;
	for (int i = 0; i < 3; i++) {
		double c1 = 1;
		double c2 = -1;
		for (int j = 0; j < 3; j++) {
			c1 *= M((i + j) % 3, j);
			c2 *= M(j, (3 + i - j) % 3);
		}
		theorical_det += c1 + c2;
	}
	assert(cmp_double(theorical_det, det(M)));
}

//test de det
void test_m4_det() {
	cout << "test_m4_det" << flush;
	assert(cmp_double(Matrix4::Identity.det(), 1));
	cout << "." << flush;
	for (int x = 0; x < DATA_M4; x++) {
		Matrix4 M1 = init_m4_data(m4_data[x]);
		assert(M1.det() == det(M1));
		double coef[5] = { 1,0.3,-4,-7.8,0 };
		for (int i = 0; i < 5; i++) {
			double k = coef[i];
			assert(cmp_double(det(M1 * k), det(M1) * pow(k, 3)));
		}
		cout << "." << flush;
		for (int y = 0; y < DATA_M4; y++) {
			Matrix4 M2 = init_m4_data(m4_data[x]);
			Matrix4 m4 = M1 * M2;
			Matrix4 M4 = M2 * M1;
			assert(cmp_double(det(m4), det(M1) * det(M2)));
			assert(cmp_double(det(m4), det(M4)));
			cout << "." << flush;
		}
		test_value_det(M1);
		cout << "." << flush;
	}
	cout << ".OK" << endl;
}
//test de inverse
void test_m4_inverse() {
	cout << "test_m4_inverse" << flush;
	assert(Matrix4::Identity.inverse() == Matrix4::Identity);
	cout << "." << flush;
	for (int x = 0; x < DATA_M4 - 1; x++) {
		Matrix4 M = init_m4_data(m4_data[x]);
		if (M.det() != 0) {
			Matrix4 M2 = M.inverse();
			assert(cmp_double(det(M2), 1 / det(M)));
			cout << "." << flush;
			assert(M2 == inverse(M));
			assert(M2 * M == M2 * M);
			assert(M2 * M == Matrix4::Identity);
			cout << "." << flush;
		}
	}
	cout << ".OK" << endl;
}