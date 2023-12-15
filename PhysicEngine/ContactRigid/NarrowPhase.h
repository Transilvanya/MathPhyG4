#pragma once
#include "../RigidBody/RigidBody.h"
#include <list>
#include "Primitive/Primitive.h"
#include "Primitive/Box.h"
#include "Primitive/Plane.h"
#include "Primitive/Sphere.h"

#include "Contacts/Contact.h"
#include <vector>

struct CollisionData
{
	Contact* contacts;
	unsigned contactsLeft;
};

class NarrowPhase
{
private:
	std::vector<Contact> contacts;

public:
	std::vector<Contact> narrowPhase(std::list<std::pair<RigidBody*, RigidBody*> > pairRigidbodies);
	void generateContacts(
		const Primitive& firstPrimitive,
		const Primitive& secondPrimitive);
	unsigned sphereAndSphere(
		const Sphere& firstPrimitive,
		const Sphere& secondPrimitive);
	unsigned sphereAndHalfSpace(
		const Sphere& sphere,
		Plane& plane);
	unsigned boxPlane(
		const Box& box,
		const Plane& plane);
	unsigned boxAndSphere(
		const Box& box,
		const Sphere& sphere);
	unsigned boxAndBox(
		const Box& firstBox,
		const Box& secondBox);
};