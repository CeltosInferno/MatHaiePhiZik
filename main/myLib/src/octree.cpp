#include "octree.hpp"

using namespace m_engine;


Octree::Octree(int depthMax, const Vector3D& Center, const Vector3D& Dimension): depthMax(depthMax), Center(Center), Dimension(Dimension){
	root = new OctreeNode(depthMax, Center, Dimension);
}

Octree::~Octree() {
	delete root;
}

//resolve potentials collisions
std::vector<std::pair<Primitive*, Primitive*>> Octree::resolveTree() {
	return root->resolveNode();
}

//insert a primitive into the tree
void Octree::insert(Primitive* p) {
	//std::cout << "Insert2 " << p->getRigidBody() << std::endl;
	root->insert(p);
}
