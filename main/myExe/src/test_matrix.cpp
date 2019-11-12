#define EPSILON 1e-15

#include <cassert>
#include <iostream>

#include "matrix3.hpp"
#include "matrix4.hpp"

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

Matrix3& init_m3_data(const double data[9]) {
	return Matrix3(data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7], data[8]);
}

//test de l'instanciation et l'affectation
void test_m3_start() {
	cout << "test_m3_start" << flush;
	//cout << "." << flush;
	cout << ".OK" << endl;
}
//test de l'egalite ou difference
void test_m3_equality() {
	cout << "test_m3_equality" << flush;
	cout << ".OK" << endl;
}
//test l'operation +, +=
void test_m3_add() {
	cout << "test_m3_add" << flush;
	cout << ".OK" << endl;
}
//test l'operation a-b, a-=b et -a
void test_m3_sub() {
	cout << "test_m3_sub" << flush;
	cout << ".OK" << endl;
}
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m3_mult() {
	cout << "test_m3_mult" << flush;
	cout << ".OK" << endl;
}
//test de det
void test_m3_det() {
	cout << "test_m3_det" << flush;
	cout << ".OK" << endl;
}
//test de inverse
void test_m3_inverse() {
	cout << "test_m3_inverse" << flush;
	cout << ".OK" << endl;
}
//test de t
void test_m3_transpose() {
	cout << "test_m3_transpose" << flush;
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

Matrix4& init_m4_data(const double data[12]) {
	return Matrix4(data[0], data[1], data[2], data[3],
		data[4], data[5], data[6], data[7],
		data[8], data[9], data[10], data[11]);
}

void test_m4_start() {
	cout << "test_m4_start" << flush;
	//cout << "." << flush;
	cout << ".OK" << endl;
}
//test de l'egalite ou difference
void test_m4_equality() {
	cout << "test_m4_equality" << flush;
	cout << ".OK" << endl;
}
//test l'operation +, +=
void test_m4_add() {
	cout << "test_m4_add" << flush;
	cout << ".OK" << endl;
}
//test l'operation a-b, a-=b et -a
void test_m4_sub() {
	cout << "test_m4_sub" << flush;
	cout << ".OK" << endl;
}
//testb l'operation *, *=, /, /= sur matrice et constante
void test_m4_mult() {
	cout << "test_m4_mult" << flush;
	cout << ".OK" << endl;
}
//test de det
void test_m4_det() {
	cout << "test_m4_det" << flush;
	cout << ".OK" << endl;
}
//test de inverse
void test_m4_inverse() {
	cout << "test_m4_inverse" << flush;
	cout << ".OK" << endl;
}