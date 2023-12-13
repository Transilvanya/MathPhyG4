#pragma once
#include "../../RigidBody/RigidBody.h"
#include "../../vector/Vector3D.h"

class Contact
{
public:
	Vector3D contactPoint;
	Vector3D contactNormal;
	float penetration;
	float restitution;
	float friction;
	std::array<RigidBody,2> rigidbodies;
};