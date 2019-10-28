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
  //test_double_operators();
  //test_exponentiation();
  //test_basic_operators();
  //test_quaternions_operations();
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
	//operator *
	//operator *=
	//operator /
	//operator /=
}

void test_exponentiation() {
	//Qlog
	//Qexp
	//Qexp double
	//Qexp Quaternion
}

void test_basic_operators() {
	//scalar
	//-
	//norm
	//sqrNorm
	//normalize
	//isNormalized
	//conjugate
	//inverse
};

void test_quaternions_operations() {
	//*
	//*=
	//diff
	//+
	//+=
	//-
	//-=
	//==
	//!=

};

