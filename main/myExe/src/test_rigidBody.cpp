#include "rigidBody.hpp"
#include "rigidBodyGravityGenerator.hpp"
#include "rigidBodyAnchoredString.hpp"

using namespace m_engine;
using namespace std;

int main() {
	RigidBody RB(1, 1);
	RigidBodyGravityGenerator RGG();
	RigidBodyAnchoredString RBAS();
	return 0;
}