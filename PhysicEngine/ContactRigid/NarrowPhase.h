#pragma once
#include "../RigidBody/RigidBody.h"
#include <list>
#include "Primitive/Primitive.h"
#include "Primitive/Box.h"
#include "Primitive/Plane.h"
#include "Primitive/Sphere.h"

#include "Contacts/Contact.h"

typedef struct CollisionData
{
	Contact* contacts;
	unsigned int contactsLeft;
} CollisionData;

class NarrowPhase
{
private:
	std::list<std::array<RigidBody*, 2>> pairRigidbodies;
	std::list<Contact*> contacts;
	void generateContacts(
		const Primitive* firstPrimitive,
		const Primitive* secondPrimitive,
		CollisionData* data);
	unsigned sphereAndSphere(
		Sphere* firstPrimitive,
		Sphere* secondPrimitive,
		CollisionData* data);
	unsigned sphereAndHalfSpace(
		Sphere* sphere,
		Plane* plane,
		CollisionData* data);
	unsigned boxPlane(
		Box* box,
		Plane* plane,
		CollisionData* data);
	unsigned boxAndSphere(
		Box* box,
		Sphere* sphere,
		CollisionData* data);
	unsigned boxAndBox(
		Box* firstBox,
		Box* secondBox,
		CollisionData* data);

public:
	NarrowPhase(std::list<std::array<RigidBody*, 2>> pairRigidbodies);
	std::list<Contact*> getContacts() { return contacts; }
	
};