#ifndef OCTREE
#define OCTREE


#include "OctreeNode.hpp"
#include "vector3d.hpp"

#include <vector>
#include <utility>

namespace m_engine {

	//class Primitive;

	class Octree {
	public:	
		Octree(int depthMax, Vector3D Center, Vector3D Dimension);
		OctreeNode* root;
		//the max depth of the tree
		int depthMax;
		//Represent the center of cube area
		Vector3D Center;
		//Represent the dimension based on Base vertex
		Vector3D Dimension;
		//insert a primitive into the tree
		void insert(Primitive* p);
		//resolve potentials collisions
		std::vector<std::pair<Primitive*, Primitive*>> resolveTree();
	};

};

#endif