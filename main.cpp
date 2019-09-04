#include <iostream>
#include "vector3d.hpp"

using namespace m_engine;

int main() {

  //mieux vaut redefinir un operateur <<
  std::cout << "potatoe " << Vector3D(0,2) << std::endl;
  return 0;
}
