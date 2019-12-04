#ifndef OCTREENODE
#define OCTREENODE

#include <vector>
#include <utility>
#include "vector3d.hpp"

class Primitive;

namespace m_engine {

	class OctreeNode {
	public:
		OctreeNode(int depth, Vector3D Min, Vector3D Max);
		std::vector<OctreeNode*> children;
		std::vector< std::pair<Primitive*, Primitive*> > resolveNode();
		void insert(Primitive* p);

	};

};

#endif