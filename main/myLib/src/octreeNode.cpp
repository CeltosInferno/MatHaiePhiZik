#include "OctreeNode.hpp"

using namespace m_engine;

OctreeNode::OctreeNode(int depthMax, const Vector3D& Center, const Vector3D& Dimension): 
	depthMax(depthMax), Center(Center),Dimension(Dimension) {}

OctreeNode::~OctreeNode() {
	for (OctreeNode* ON : children) {
		delete ON;
	}
	children.clear();
}


//return all potentials collisions in this area
std::vector<std::pair<Primitive*, Primitive*>> OctreeNode::resolveNode() {
	std::vector < std::pair<Primitive*, Primitive*>> potentialCollisions;
	//when tree's bottom is reached or there is no children
	if (depthMax <= 0 || children.size()<=0) {
		//iteration on all primitives recorded on this node
		for (int i = 0; i < primitives.size(); i++) {
			for (int j = i + 1; j < primitives.size(); j++) {
				potentialCollisions.push_back( std::make_pair(primitives[i], primitives[j]) );
			}
		}
	}
	//if child nodes exists
	else {
		//checking all collisions on children
		for (OctreeNode* ON : children) {
			std::vector < std::pair<Primitive*, Primitive*>> tempResult = ON->resolveNode();
			//TO IMPROVE BY CHEKING IF THERE IS NO DOUBLE
			potentialCollisions.insert(potentialCollisions.end(), tempResult.begin(), tempResult.end());
		}
	}
	return potentialCollisions;
}

void OctreeNode::insert(Primitive* p) {
	//std::cout << "Insert3 " << p->getRigidBody() << " " << depthMax << std::endl;
	//on a leaf, just store the primitive
	if (depthMax <= 0) {
		primitives.push_back(p);
		//std::cout << "Put a Primitive Here :3 " << p << " " <<primitives.size() << std::endl;
	}
	//if not on a leave
	else {
		//if child nodes are not created, create them
		if (children.size() == 0) {
			Vector3D halfDimension = Dimension / 2;

			Vector3D center1 = Center + Vector3D(halfDimension.x, halfDimension.y, halfDimension.z);
			Vector3D center2 = Center + Vector3D(halfDimension.x, halfDimension.y, -halfDimension.z);
			Vector3D center3 = Center + Vector3D(halfDimension.x, -halfDimension.y, halfDimension.z);
			Vector3D center4 = Center + Vector3D(halfDimension.x, -halfDimension.y, -halfDimension.z);
			Vector3D center5 = Center + Vector3D(-halfDimension.x, halfDimension.y, halfDimension.z);
			Vector3D center6 = Center + Vector3D(-halfDimension.x, halfDimension.y, -halfDimension.z);
			Vector3D center7 = Center + Vector3D(-halfDimension.x, -halfDimension.y, halfDimension.z);
			Vector3D center8 = Center + Vector3D(-halfDimension.x, -halfDimension.y, -halfDimension.z);

			children.push_back(new OctreeNode(depthMax - 1, center1, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center2, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center3, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center4, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center5, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center6, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center7, halfDimension));
			children.push_back(new OctreeNode(depthMax - 1, center8, halfDimension));
		}
		//checking if primitive is in child nodes
		for (OctreeNode* ON : children) {
			//std::cout << "Bleep " << std::endl;
			if (p->isInArea(ON->Center, ON->Dimension)) {
				ON->insert(p);
			}
		}
	}
}
