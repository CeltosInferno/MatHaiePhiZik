#ifndef OCTREENODE
#define OCTREENODE

#include <vector>
#include <utility>
#include "vector3d.hpp"
#include "primitive.hpp"

namespace m_engine {

	class OctreeNode {
	public:
		OctreeNode(int depthMax, Vector3D Center, Vector3D Dimension);
		//list of the eight children 
		std::vector<OctreeNode*> children;
		//liste of the primitives attached to the node
		std::vector<Primitive*> primitives;

		//return all potentials collisions in this area
		std::vector< std::pair<Primitive*, Primitive*> > resolveNode();
		//instert a primitive into concerned areas
		void insert(Primitive* p);

		//represent the maximal depth
		int depthMax;
		//center represent the center of the area cover by the node
		Vector3D Center;
		//dimension is half-radius on each coordinate
		Vector3D Dimension;
	};

};

#endif