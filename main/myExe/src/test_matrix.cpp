#define EPSILON 0.00000000001

#include <cassert>
#include <iostream>

#include "matrix3.hpp"
#include "matrix4.hpp"

using namespace m_engine;
using namespace std;

void testMatrix3() {
	cout << "test of Matrix3:" << endl;
	cout << Matrix3() << endl;
	cout << "test of Matrix3 OK" << endl;
}

void testMatrix4() {
	cout << "test of Matrix4:" << endl;
	cout << Matrix4() << endl;
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