#include "octree.hpp"

using namespace m_engine;


Octree::Octree(int depthMax, Vector3D Center, Vector3D Dimension): depthMax(depthMax), Center(Center), Dimension(Dimension){
	root = new OctreeNode(depthMax, Center, Dimension);
}

//resolve potentials collisions
std::vector<std::pair<Primitive*, Primitive*>> Octree::resolveTree() {
	return root->resolveNode();
}

//insert a primitive into the tree
void Octree::insert(Primitive* p) {
	root->insert(p);
}
