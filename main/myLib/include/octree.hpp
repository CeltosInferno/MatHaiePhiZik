#ifndef OCTREE
#define OCTREE


#include "OctreeNode.hpp"
#include "vector3d.hpp"

#include <vector>
#include <utility>

namespace m_engine {

	//This class represent a tree hat can find collision between primitives
	class Octree {
	public:	
		Octree(int depthMax, const Vector3D& Center, const Vector3D& Dimension);
		~Octree();
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
