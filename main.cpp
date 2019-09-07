#include <iostream>
#include "vector3d.hpp"
#include "particle.hpp"

using namespace m_engine;

int main() {
  std::cout << "potatoe " << Vector3D(0,2) << std::endl;
  Vector3D a(1,2,3);
  a *= 2;
  std::cout << "a " << a << std::endl;
  Vector3D b(3, 2, 1);
  Vector3D c = a -b;
  std::cout << "c " << c << std::endl;
  c = 3*a;
  std::cout << "c " << c << std::endl;
  double x = scalar(a,b);
  std::cout << "x " << x << std::endl;
  return 0;

}
