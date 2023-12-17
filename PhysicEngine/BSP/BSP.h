#pragma once

#include <vector>
#include <list>

#include "../RigidBody/RigidBody.h"
#include "Tree/Node.h"

using namespace std;

class BSP
{
public :

	BSP(vector<RigidBody> bodys);
	Node* order(Node* root, int iteration);
	list<pair<RigidBody*, RigidBody*>> getPotentialCollision();

private :

	list<pair<RigidBody*, RigidBody*>> parcoursPrefixe(Node* root);
	std::vector<RigidBody> furthestPoints(const std::vector<RigidBody>& bodys);
	float distance(RigidBody r1, RigidBody r2);
	list<RigidBody> getSameAndLowerLevelChild(Node* child);
	list<RigidBody> getAllRigidBody(Node* parent);
	Node root;


};

