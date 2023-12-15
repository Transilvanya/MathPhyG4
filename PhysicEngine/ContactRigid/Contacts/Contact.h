#pragma once
#include "../../RigidBody/RigidBody.h"
#include "../../vector/Vector3D.h"

class Contact
{
public:

	Contact() {};

	Vector3D contactPoint;
	Vector3D contactNormal;
	float penetration;
	float restitution;
	float friction;
	std::pair<RigidBody*, RigidBody*> rigidbodies;
};