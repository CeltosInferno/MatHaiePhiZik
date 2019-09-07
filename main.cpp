#include <iostream>
#include "vector3d.hpp"
#include "particle.hpp"

using namespace m_engine;

int main() {

  //mieux vaut redefinir un operateur <<
  std::cout << "potatoe " << Vector3D(0,2) << std::endl;
  std::string test;
  std::cin >> test;
  return 0;

}
