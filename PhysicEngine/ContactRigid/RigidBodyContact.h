
#ifndef RIGIDBODYCONTACT_CLASS_H
#define RIGIDBODYCONTACT_CLASS_H

#include "../RigidBody/RigidBody.h"

class RigidBodyContact
{

public:
	RigidBody* rigidbodies[2];

	// 0 - 1
	// elasticity of collision
	float restitution;

	//distance of penetration of contact, aka lenght where overlap
	float penetration;


	Vector3D contactNormal;

	//global coord

	Vector3D RBAnchorPoint[2];


	RigidBodyContact(RigidBody* p1, RigidBody* p2, float _restitution, float _penetration, Vector3D _contactNormal, Vector3D anchor1, Vector3D anchor2)
	{
		rigidbodies[0] = p1;
		rigidbodies[1] = p2;
		restitution = _restitution;
		penetration = _penetration;
		contactNormal = _contactNormal;

		RBAnchorPoint[0] = anchor1;
		RBAnchorPoint[1] = anchor2;
	}


};


#endif
