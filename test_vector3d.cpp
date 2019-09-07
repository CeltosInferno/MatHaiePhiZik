#include <iostream>
#include "vector3d.hpp"

#include <cassert>

using namespace m_engine;
using namespace std;

//test de l'instanciation et l'affectation
void test_start();
//test de l'egalite ou difference
void test_equality();
//test l'operation +, +=
void test_add();
//test l'operation a-b, a-=b et -a
void test_sub();
//testb l'operation *, *=, /, /= sur vecteur et constante
void test_mult();
//test de l'operation u * v (u et v vecteurs)
void test_mult2();
//test de scalar, norm, sqrNorm et normalize
void test_norm();
//test de cross
void test_cross();
//test de distance
void test_distance();
//test du produit multiple
void test_tripleProduct();

int main() {
  cout << "\ntest_vector3d:" << endl;
  test_start();
  test_equality();
  test_add();
  test_sub();
  test_mult();
  test_mult2();
  test_norm();
  test_cross();
  test_distance();
  test_tripleProduct();
  cout << "test_vector3d OK" << endl;
  return 0;
}

void test_start() {
  cout << "test_start" << flush;
  Vector3D a;
  assert(a.x == 0);
  assert(a.y == 0);
  assert(a.z == 0);
  cout << "." << flush;
  Vector3D b(2,5,-1);
  assert(b.x == 2);
  assert(b.y == 5);
  assert(b.z == -1);
  cout << "." << flush;
  a = b;
  assert(a.x == 2);
  assert(a.y == 5);
  assert(a.z == -1);
  cout << "." << flush;
  assert(a[0] == 2);
  assert(a[1] == 5);
  assert(a[2] == -1);
  cout << ".OK" << endl;
}

void test_equality() {
  cout << "test_equality" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  Vector3D c;
  assert(a == a);
  cout << "." << flush;
  assert(b != a);
  cout << "." << flush;
  assert(a != b);
  cout << "." << flush;
  c = a;
  assert(c == a);
  cout << "." << flush;
  assert(a == c);
  cout << ".OK" << endl;
}

void test_add() {
  cout << "test_add" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  Vector3D c = a + b;
  Vector3D d(3, 8, 1);
  assert(d == c);
  cout << "." << flush;
  a += b;
  assert(a == d);
  cout << "." << flush;
  c = b + b;
  d = Vector3D(2, 6, 4);
  assert(c == d);
  cout << ".OK" << endl;
}

void test_sub() {
  cout << "test_sub" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  Vector3D c = a - b;
  Vector3D d(1, 2, -3);
  assert(d == c);
  cout << "." << flush;
  a -= b;
  assert(a == d);
  cout << "." << flush;
  c = -b;
  d = Vector3D(-1, -3, -2);
  assert(c == d);
  cout << ".OK" << endl;
}

void test_mult() {
  cout << "test_mult" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  int k = 6;
  Vector3D c = a * k;
  Vector3D d(12, 30, -6);
  assert(d == c);
  cout << "." << flush;
  a *= k;
  assert(a == d);
  cout << "." << flush;
  c = 3*b;
  d = Vector3D(3, 9, 6);
  assert(c == d);
  cout << "." << flush;
  
  c /= 3;
  assert(c == b);
  cout << "." << flush;
  c = d/2;
  d = Vector3D(1.5, 4.5, 3);
  assert(c == d);
  cout << ".OK" << endl;
}

void test_mult2() {
  cout << "test_mult2" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  Vector3D c = a * b;
  Vector3D d(2, 15, -2);
  
  assert(d == c);
  cout << "." << flush;
  c *= a;
  d = Vector3D(4, 75, 2);
  assert(d == c);
  cout << ".OK" << endl;
}

void test_norm() {
  cout << "test_norm" << flush;
  Vector3D a(2,5,-1);
  Vector3D b(1,3,2);
  double c = scalar(a,b);

  //test de scalar
  assert(c == scalar(b,a));
  cout << "." << flush;
  assert(c == a.scalar(b));
  cout << "." << flush;
  assert(c == b.scalar(a));
  cout << "." << flush;
  assert(c == a.scalar(b));
  cout << "." << flush;
  assert(c == 15);
  cout << "." << flush;

  //test de norm^2
  c = sqrNorm(a);
  cout << "." << flush;
  assert(c == a.sqrNorm());
  cout << "." << flush;
  assert(c == 30);
  cout << "." << flush;

  c = sqrNorm(b);
  cout << "." << flush;
  assert(c == b.sqrNorm());
  cout << "." << flush;
  assert(c == 14);
  cout << "." << flush;

  //test de norm
  a = Vector3D(3,4,0);
  c = norm(a);
  cout << "." << flush;
  assert(c == a.norm());
  cout << "." << flush;
  assert(c == 5);
  cout << "." << flush;

  //test de normalize
  b = a.normalize();
  assert(b == normalize(a));
  cout << "." << flush;
  assert(b.x == 0.6);
  cout << "." << flush;
  assert(b.y == 0.8);
  cout << "." << flush;
  assert(b.z == 0);
  cout << "." << flush;
  assert(norm(b) == 1);
  cout << "." << flush;

  b = Vector3D(0,0,0);
  assert(b.normalize() == b);
  
  cout << ".OK" << endl;
}

void sub_test_cross(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
  assert(a.cross(b) == cross(a,b));
  assert(a.cross(b) == -b.cross(a));
  cout << "." << flush;
  assert(a.cross(b) == c);
  cout << "." << flush;
}

void test_cross() {
  cout << "test_cross" << flush;
  //test sur les vecteurs cartesiens
  Vector3D x(1,0,0);
  Vector3D y(0,1,0);
  Vector3D z(0,0,1);
  sub_test_cross(x,y,z);
  sub_test_cross(y,z,x);
  sub_test_cross(z,x,y);
  sub_test_cross(y,x,-z);
  sub_test_cross(z,y,-x);
  sub_test_cross(x,z,-y);
  //test sur des vecteurs quelconques
  x = Vector3D(4,1,0);
  y = Vector3D(0,1,2);
  z = Vector3D(2,-8,4);
  sub_test_cross(x,y,z);
  cout << ".OK" << endl;
}

void test_distance() {
  cout << "test_distance" << flush;
  Vector3D a(2,0,1);
  Vector3D b(-4,3,3);
  double c = a.distance(b);
  assert(c == b.distance(a));
  cout << "." << flush;
  assert(c == m_engine::distance(b,a));
  cout << "." << flush;
  assert(c == 7);
  cout << ".OK" << endl;
}

void test_tripleProduct() {
  cout << "test_tripleProduct" << flush;
  Vector3D a(2,0,0);
  Vector3D b(0,2,0);
  Vector3D c(0,0,2);
  double v = a.tripleProduct(b,c);
  assert(v == tripleProduct(a,b,c));
  cout << "." << flush;
  assert(v == 8);
  cout << ".OK" << endl;
}
