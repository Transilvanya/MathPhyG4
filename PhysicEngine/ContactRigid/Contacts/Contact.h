#pragma once
#include "../../RigidBody/RigidBody.h"
#include "../../vector/Vector3D.h"
#include <vector>

class Contact
{
public:
	Contact(
		Vector3D contactPoint,
		Vector3D contactNormal,
		float penetration,
		float restitution,
		float friction,
		std::array<RigidBody*, 2> rigidbodies
	) {
		Contact::contactPoint = contactPoint;
		Contact::contactNormal = contactNormal;
		Contact::penetration = penetration;
		Contact::restitution = restitution;
		Contact::friction = friction;
		Contact::rigidbodies = rigidbodies;
	}
	Vector3D contactPoint;
	Vector3D contactNormal;
	float penetration;
	float restitution;
	float friction;
	std::array<RigidBody*, 2> rigidbodies;
};