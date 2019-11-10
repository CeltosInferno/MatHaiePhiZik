#include "rigidBody.hpp"
#include "rigidBodyGravityGenerator.hpp"
#include "rigidBodyAnchoredString.hpp"
#include "rigidBodyDragGenerator.hpp"
#include "rigidBodyElasticString.hpp"
#include "rigidBodyFloatingGenerator.hpp"
#include "rigidBodyStiffSpring.hpp"
#include "rigidBodyString.hpp"

using namespace m_engine;
using namespace std;

int main() {
	RigidBody RB(1, 1);
	RigidBodyGravityGenerator RGG(1);
	RigidBodyAnchoredString RBAS = RigidBodyAnchoredString(Vector3D(0,0,0) , 1, 1);
	RigidBodyDragGenerator RBDG = RigidBodyDragGenerator(1,1);
	RigidBodyElasticString RBES = RigidBodyElasticString(RB, 1, 1, Vector3D(0, 0, 0));
	RigidBodyFloatingGenerator RBFG = RigidBodyFloatingGenerator(1, 1, 1);
	RigidBodyStiffSpring RBSS = RigidBodyStiffSpring(Vector3D(0, 0, 0), 1, 1);
	RigidBodyString RBS = RigidBodyString(RB, Vector3D(0,0,0), 1, 1);
	RGG.updateForce(RB,1.0);
	RBAS.updateForce(RB, 1.0);
	RBDG.updateForce(RB, 1.0);
	RBES.updateForce(RB, 1.0);
	RBFG.updateForce(RB, 1.0);
	RBSS.updateForce(RB, 1.0);
	RBS.updateForce(RB, 1.0);
	return 0;
}