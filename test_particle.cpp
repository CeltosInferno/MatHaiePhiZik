#include <iostream>
#include "vector3d.hpp"
#include "particle.hpp"

#include <cassert>

using namespace m_engine;
using namespace std;

void test_start() {
  cout << "test_start" << flush;
  cout << "OK" << endl;
}

int main() {
  cout << "\ntest_particle:" << endl;
  test_start();
  cout << "test_particle OK" << endl;
  return 0;
}
