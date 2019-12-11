#include "octree.hpp"

using namespace m_engine;

//This class represent an tree that can find collision between primitives

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
	root->insert(p);
}
