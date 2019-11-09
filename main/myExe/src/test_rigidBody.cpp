#include "rigidBody.hpp"
#include "rigidBodyGravityGenerator.hpp"
#include "rigidBodyAnchoredString.hpp"
#include "rigidBodyDragGenerator.hpp"

using namespace m_engine;
using namespace std;

int main() {
	RigidBody RB(1, 1);
	RigidBodyGravityGenerator RGG(1);
	RigidBodyAnchoredString RBAS = RigidBodyAnchoredString(Vector3D(0,0,0) , 1, 1);
	RigidBodyDragGenerator RBDG = RigidBodyDragGenerator(1,1);
	RGG.updateForce(RB,1.0);
	RBAS.updateForce(RB, 1.0);
	RBDG.updateForce(RB, 1.0);
	//particleElasticString
	//particleFloatingGenerator
	//particleRod
	//particleStiffSpring
	//particleString
	return 0;
}