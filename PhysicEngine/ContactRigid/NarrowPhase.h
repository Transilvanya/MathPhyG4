#pragma once
#include "../RigidBody/RigidBody.h"
#include <list>
#include "Primitive/Primitive.h"
#include "Primitive/Box.h"
#include "Primitive/Plane.h"
#include "Primitive/Sphere.h"

#include "Contacts/Contact.h"

struct CollisionData
{
	Contact* contacts;
	unsigned contactsLeft;
};

class NarrowPhase
{
private:
	std::list<RigidBody[2]> pairRigidbodies;
	std::list<Contact> contacts;

public:
	std::list<Contact> narrowPhase(std::list<RigidBody[2]> pairRigidbodies);
	void generateContacts(
		const Primitive& firstPrimitive,
		const Primitive& secondPrimitive,
		CollisionData* data);
	unsigned sphereAndSphere(
		const Sphere& firstPrimitive,
		const Sphere& secondPrimitive,
		CollisionData* data);
	unsigned sphereAndHalfSpace(
		const Sphere& sphere,
		Plane& plane,
		CollisionData* data);
	unsigned boxPlane(
		const Box& box,
		const Plane& plane,
		CollisionData* data);
	unsigned boxAndSphere(
		const Box& box,
		const Sphere& sphere,
		CollisionData* data);
	unsigned boxAndBox(
		const Box& firstBox,
		const Box& secondBox,
		CollisionData* data);
};