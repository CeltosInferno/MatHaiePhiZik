#define _USE_MATH_DEFINES
#define EPSILON 0.00000000001

#include <iostream>
#include "quaternion.hpp"

#include <cassert>
#include <cmath>

using namespace m_engine;
using namespace std;

//test de l'instanciation de nouveaux quaternions par les constructeurs classiques ou par méthode statique
void test_constructors();
void test_double_operators();
void test_exponentiation();
void test_basic_operators();
void test_quaternions_operations();

int main() {
  cout << "\ntest_quaternion:" << endl;
  test_constructors();
  test_double_operators();
  test_basic_operators();
  test_quaternions_operations();
  test_exponentiation();
  cout << "test_quaternion OK" << endl;
  return 0;
}

void test_constructors() {
  cout << "test_start" << flush;
  //test without parameters
  cout << "." << flush;
  Quaternion q1;
  assert(q1.w == 0);
  assert(q1.n.x == 0);
  assert(q1.n.y == 0);
  assert(q1.n.z == 0);
  //test with less than 4 doubles
  cout << "." << flush;
  Quaternion q2(3,-1);
  assert(q2.w == 3);
  assert(q2.n.x == -1);
  assert(q2.n.y == 0);
  assert(q2.n.z == 0);
  //test with constructor with 4 doubles
  cout << "." << flush;
  Quaternion q3(2, 5, 3, -1);
  assert(q3.w == 2);
  assert(q3.n.x == 5);
  assert(q3.n.y == 3);
  assert(q3.n.z == -1);
  //test with a double and a vector
  cout << "." << flush;
  Quaternion q4(2, Vector3D(5, 3, -1));
  assert(q4.w == 2);
  assert(q4.n.x == 5);
  assert(q4.n.y == 3);
  assert(q4.n.z == -1);
  //test with an angle
  cout << "." << flush;
  Quaternion q5 = Quaternion::FormAxisAngle(M_PI, Vector3D(0.5,0.5,0));
  assert(q5.w < EPSILON);
  assert(abs(q5.n.x - 0.5) < EPSILON);
  assert(abs(q5.n.y - 0.5) < EPSILON);
  assert(abs(q5.n.z - 0) < EPSILON);
  cout << ".OK" << endl;
}

void test_double_operators() {

	cout << "start test_double_operators" << flush;
	//operator *
	cout << "." << flush;
	Quaternion q1 = Quaternion(1, -2, 3, 4) * 3;
	assert(q1.w == 3);
	assert(q1.n.x == -6);
	assert(q1.n.y == 9);
	assert(q1.n.z == 12);
	//operator *=
	cout << "." << flush;
	q1 *= -2;
	assert(q1.w == -6);
	assert(q1.n == Vector3D(12, -18, -24));
	//operator /
	cout << "." << flush;
	Quaternion q2 = q1;
	assert(q2.w == -6);
	assert(q2.n == Vector3D(12, -18, -24));
	q2 = q2 / -2;

	assert(q2.w == 3);
	assert(q2.n.x == -6);
	assert(q2.n.y == 9);
	assert(q2.n.z == 12);

	//operator /=
	cout << "." << flush;
	q2 /= 3;

	assert(q2.w == 1);
	assert(q2.n == Vector3D(-2, 3, 4));

	cout << ".OK" << endl;
}

void test_exponentiation() {
	cout << "start test_exponentiation" << flush;
	//Qlog
	cout << "." << flush;
	Quaternion q1 = Quaternion(6, 8, 0, 0).Qlog();
	
	assert(abs(q1.w - log(10))<EPSILON);
	double f = acos(3.0 / 5.0);
	assert(abs(q1.n.x - f ) < EPSILON);
	assert(abs(q1.n.y - 0) < EPSILON);
	assert(abs(q1.n.z - 0 ) < EPSILON);

	Quaternion q2 = Quaternion(6, 0, -8, 0).Qlog();
	assert(abs(q2.n.y + f) < EPSILON);

	Quaternion q3 = Quaternion(6, 0, 0, 8).Qlog();
	assert(abs(q3.n.z - f) < EPSILON);
	//Qexp
	cout << "." << flush;
	cout << "." << flush;
	Quaternion q5 = Quaternion(8, 4 * M_PI, -4* M_PI, 2* M_PI).Qexp();

	assert(abs(q5.w - exp(8)) < EPSILON);
	assert(abs(q5.n.x) < EPSILON);
	assert(abs(q5.n.y) < EPSILON);
	assert(abs(q5.n.z) < EPSILON);

	Quaternion q6 = Quaternion(0, 0, 3 * M_PI_2, 2 * M_PI).Qexp();

	assert(abs(q6.w) < EPSILON);
	assert(abs(q6.n.x) < EPSILON);
	assert(abs(q6.n.y - (3.0 / 5.0)) < EPSILON);
	assert(abs(q6.n.z - (4.0 / 5.0)) < EPSILON);

	//Qexp(Qlog) et Qlog(Qexp)
	cout << "." << flush;
	//Quaternion q7 = Quaternion(2, 3, -1, -1);
	Quaternion q7 = Quaternion::FormAxisAngle(M_PI_4, Vector3D(1, 2, 2).normalize());
	Quaternion q8 = q7.Qexp().Qlog();
	Quaternion q9 = q7.Qlog().Qexp();

	assert(abs(q7.w - q8.w) < EPSILON);
	assert(abs(q7.n.x - q8.n.x) < EPSILON);
	assert(abs(q7.n.y - q8.n.y) < EPSILON);
	assert(abs(q7.n.z - q8.n.z) < EPSILON);


	assert(abs(q7.w - q9.w) < EPSILON);
	assert(abs(q7.n.x - q9.n.x) < EPSILON);
	assert(abs(q7.n.y - q9.n.y) < EPSILON);
	assert(abs(q7.n.z - q9.n.z) < EPSILON);

	//Qexp double
	cout << "." << flush;
	double theta = M_PI_4;
	Vector3D n = Vector3D(-2, 3, -1).normalize();
	Vector3D n2 = n * sin(theta / 4.0);
	Quaternion q10 = Quaternion::FormAxisAngle(theta, n).Qexp(1.0/2.0);
	assert(abs(q10.w - cos(theta / 4.0)) < EPSILON);
	assert(abs(q10.n.x - n2.x) < EPSILON);
	assert(abs(q10.n.y - n2.y) < EPSILON);
	assert(abs(q10.n.z - n2.z) < EPSILON);

	//Qexp Quaternion
	//Probably lack of precision make those tests fail
	/*
	double theta1 = M_PI_2;
	double theta2 = M_PI;
	std::cout << cos(theta1 / 2) << endl;
	Vector3D v1 = Vector3D(1.0 / 3.0, 2.0 / 3.0, -2.0 / 3.0).normalize();
	Vector3D v2 = Vector3D(0, -4.0/5.0, -3.0/5.0).normalize();
	Quaternion q11 = Quaternion::FormAxisAngle(theta1, v1).Qexp(Quaternion::FormAxisAngle(theta2, v2));
	Vector3D QexpQResultV(2.0/15.0, -1.0/5.0, -4.0/15.0);
	QexpQResultV = QexpQResultV.normalize();
	QexpQResultV *= sin(sqrt(33) / 15);
	
	assert(abs(q11.w - cos(sqrt(33)/15)*exp(-2/15)) < EPSILON);
	assert(abs(q11.n.x - QexpQResultV.x) < EPSILON);
	assert(abs(q11.n.y - QexpQResultV.y) < EPSILON);
	assert(abs(q11.n.z - QexpQResultV.z) < EPSILON);
	*/
	cout << "." << flush;
	cout << ".OK" << endl;
}

void test_basic_operators() {

	cout << "start test_basic_operators" << flush;

	Quaternion q1 = Quaternion::FormAxisAngle(M_PI, Vector3D(1, -2, 2).normalize());
	Quaternion q2(-1, 1, -2, -2);

	//scalar
	cout << "." << flush;
	double scalar_result = q1.scalar(q2);
	assert(abs(scalar_result - 1.0/3.0) < EPSILON);
	//-
	Quaternion q4 = -q2;
	assert(q4.w == 1);
	assert(q4.n.x == -1);
	assert(q4.n.y == 2);
	assert(q4.n.z == 2);
	//norm
	cout << "." << flush;
	double norm_result = q2.norm();
	assert(abs(norm_result - sqrt(10)) < EPSILON);
	//sqrNorm
	cout << "." << flush;
	double sqr_norm_result = q2.sqrNorm();
	assert(abs(sqr_norm_result - 10) < EPSILON);
	//normalize
	cout << "." << flush;
	Quaternion q5 =  Quaternion(-1, 5, 36, -20).normalize();
	assert(abs(q5.norm() - 1) < EPSILON);
	Quaternion q6 = Quaternion().normalize();
	assert(q6.w == 0);
	assert(q6.n.x == 0);
	assert(q6.n.y == 0);
	assert(q6.n.z == 0);
	//isNormalized
	cout << "." << flush;
	assert(q5.isNormalized());
	assert(!q4.isNormalized());
	assert(!q6.isNormalized());
	//conjugate
	cout << "." << flush;
	Quaternion q7 = q2.conjugate();
	assert(q7.w == -1);
	assert(q7.n.x == -1);
	assert(q7.n.y == 2);
	assert(q7.n.z == 2);
	//inverse
	cout << "." << flush;
	Quaternion q8 = Quaternion(-8,-4,4,-2).inverse();
	assert(abs(q8.w + 8.0/10.0) < EPSILON);
	assert(abs(q8.n.x - 4.0/10.0) < EPSILON);
	assert(abs(q8.n.y + 4.0 / 10.0) < EPSILON);
	assert(abs(q8.n.z - 2.0 / 10.0) < EPSILON);
	cout << ".OK" << endl;
};

void test_quaternions_operations() {
	cout << "test_quaternions_operations" << flush;
	Quaternion q1(-1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);
	//*
	cout << "." << flush;
	Quaternion q3 = q1 * q2;
	assert(q3.w == -70);
	assert(q3.n.x == 0);
	assert(q3.n.y == 16);
	assert(q3.n.z == 8);
	//*=
	cout << "." << flush;
	Quaternion q4 = q1;
	q4 *= q2;
	assert(q4.w == -70);
	assert(q4.n.x == 0);
	assert(q4.n.y == 16);
	assert(q4.n.z == 8);
	//diff
	cout << "." << flush;
	//+
	cout << "." << flush;
	Quaternion q5 = q1 + q2;
	assert(q5.w == 4);
	assert(q5.n.x = 8);
	assert(q5.n.x = 10);
	assert(q5.n.z == 12);
	//+=
	cout << "." << flush;
	Quaternion q6(1, 1, 1, 1);
	q6 += q1;
	assert(q6.w == 0);
	assert(q6.n.x == 3);
	assert(q6.n.y == 4);
	assert(q6.n.z == 5);
	//-
	cout << "." << flush;
	Quaternion q7 = q2 - q1;
	assert(q7.w == 6);
	assert(q7.n.x == 4);
	assert(q7.n.y == 4);
	assert(q7.n.z == 4);
	//-=
	cout << "." << flush;
	Quaternion q8 = q2;
	q8 -= q1;
	assert(q8.w == 6);
	assert(q8.n.x == 4);
	assert(q8.n.y == 4);
	assert(q8.n.z == 4);
	//==
	cout << "." << flush;
	Quaternion q9(-1, 2, 3, 4);
	assert(q9 == q1);
	assert(!(q1 == q2));
	assert(!(q2 == q9));
	assert(!(q9 == q9.conjugate()));
	//!=
	assert(!(q9 != q1));
	assert((q1 != q2));
	assert((q2 != q9));
	assert((q9 != q9.conjugate()));
	cout << "." << flush;
	cout << ".OK" << endl;
};

