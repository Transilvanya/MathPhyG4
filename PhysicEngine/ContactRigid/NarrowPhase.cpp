#include "NarrowPhase.h"

std::vector<Contact> NarrowPhase::narrowPhase(std::list<std::pair<RigidBody*, RigidBody*> > pairRigidbodies)
{
	Primitive firstPrimitive;
	Primitive secondPrimitive;
	for (std::pair<RigidBody*, RigidBody*> pair : pairRigidbodies)
	{
		firstPrimitive.body = pair.first;
		secondPrimitive.body = pair.second;
		firstPrimitive.offset = pair.first->GettransformMatrix();
		secondPrimitive.offset = pair.second->GettransformMatrix();
		if (pair.first->getType() == TypeRigidBody::CUBOID)
		{
			if(pair.first->getIsStatic() == true)
				firstPrimitive.type = Primitive::PLANE;
			else if (pair.first->getIsStatic() == false)
			firstPrimitive.type = Primitive::BOX;
		}
		else if (pair.first->getType() == TypeRigidBody::SPHERE)
		{
			firstPrimitive.type = Primitive::SPHERE;
		}

		if (pair.second->getType() == TypeRigidBody::CUBOID)
		{
			secondPrimitive.type = Primitive::BOX;
		}
		else if (pair.second->getType() == TypeRigidBody::SPHERE)
		{
			secondPrimitive.type = Primitive::SPHERE;
		}

		generateContacts (firstPrimitive, secondPrimitive);
	}
	return contacts;
}

void NarrowPhase::generateContacts(const Primitive& firstPrimitive, const Primitive& secondPrimitive)
{
	if (firstPrimitive.body == nullptr || secondPrimitive.body == nullptr)
		return;
	if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::SPHERE)
	{

		sphereAndSphere((Sphere&)firstPrimitive, (Sphere&)secondPrimitive);
	}
	else if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::PLANE)
	{
		sphereAndHalfSpace((Sphere&)firstPrimitive, (Plane&)secondPrimitive);
	}
	else if (firstPrimitive.type == Primitive::PLANE && secondPrimitive.type == Primitive::SPHERE)
	{
		sphereAndHalfSpace((Sphere&)secondPrimitive, (Plane&)firstPrimitive);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::PLANE)
	{
		boxPlane((Box&)firstPrimitive, (Plane&)secondPrimitive);
	}
	else if (firstPrimitive.type == Primitive::PLANE && secondPrimitive.type == Primitive::BOX)
	{
		boxPlane((Box&)secondPrimitive, (Plane&)firstPrimitive);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::SPHERE)
	{
		boxAndSphere((Box&)firstPrimitive, (Sphere&)secondPrimitive);
	}
	else if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::BOX)
	{
		boxAndSphere((Box&)secondPrimitive, (Sphere&)firstPrimitive);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::BOX)
	{
		boxAndBox((Box&)firstPrimitive, (Box&)secondPrimitive);
	}

}

unsigned NarrowPhase::sphereAndSphere(
	const Sphere& firstPrimitive,
	const Sphere& secondPrimitive) {

	Vector3D positionOne = firstPrimitive.body->getPosition();
	Vector3D positionTwo = secondPrimitive.body->getPosition();

	Vector3D midline = positionOne - positionTwo;
	float size = midline.distance();
	float distance = ((RigidSphere*)firstPrimitive.body)->getRadius() + ((RigidSphere*)secondPrimitive.body)->getRadius();

	if(size <= 0.0f || size >= distance)
		return 0;

	Vector3D normal = midline * (1.0f / size);

	Contact* contact = new Contact();
	contact->rigidbodies.first = firstPrimitive.body;
	contact->rigidbodies.second = secondPrimitive.body;
	contact->restitution = 1;
	contact->contactNormal = normal;
	contact->contactPoint = positionOne + midline * 0.5f;
	contact->penetration = (distance - size);
	contacts.push_back(*contact);
	return 1;
}

unsigned NarrowPhase::sphereAndHalfSpace(const Sphere& sphere, Plane& plane)
{
	Vector3D positionOne = sphere.body->getPosition();
	
	float distance = (positionOne&plane.normal) - sphere.radius - plane.offset;

	if(distance >= 0.0f)
		return 0;
	//create the contact

	Contact* contact = new Contact();
	contact->rigidbodies.first = sphere.body;
	contact->rigidbodies.second = plane.body;
	contact->contactNormal = plane.normal;
	contact->penetration = -distance;
	contact->contactPoint = positionOne - (plane.normal * (distance + sphere.radius));
	contacts.push_back(*contact);
	return 1;
}

unsigned NarrowPhase::boxPlane(const Box& box, const Plane& plane)
{
	Vector3D vertex[8] = {
		Vector3D(-box.halfSize.getX(), -box.halfSize.getY(),-box.halfSize.getZ()),
		Vector3D(-box.halfSize.getX(), -box.halfSize.getY(), box.halfSize.getZ()),
		Vector3D(-box.halfSize.getX(), box.halfSize.getY(), -box.halfSize.getZ()),
		Vector3D(-box.halfSize.getX(), box.halfSize.getY(), box.halfSize.getZ()),
		Vector3D(box.halfSize.getX(), -box.halfSize.getY(), -box.halfSize.getZ()),
		Vector3D(box.halfSize.getX(), -box.halfSize.getY(), box.halfSize.getZ()),
		Vector3D(box.halfSize.getX(), box.halfSize.getY(), -box.halfSize.getZ()),
		Vector3D(box.halfSize.getX(), box.halfSize.getY(), box.halfSize.getZ())
	};

	for (int i = 0; i < 8; i++)
	{
		vertex[i] = box.offset * vertex[i];
	}

	for (int i = 0; i < 8; i++)
	{
		float distance = vertex[i] & plane.normal;
		if (distance <= plane.offset)
		{
			Contact* contact = new Contact();
			contact->rigidbodies.first = box.body;
			contact->rigidbodies.second = plane.body;
			contact->contactNormal = plane.normal;
			contact->penetration = plane.offset - distance;
			contact->contactPoint = vertex[i];
			contacts.push_back(*contact);
		}
	}

	return 1;
}

unsigned NarrowPhase::boxAndSphere(const Box& box, const Sphere& sphere)
{
	Vector3D center = sphere.body->getPosition();
	Vector3D relativeCenter = box.offset * center;

	// Early-out check to see if we can exclude the contact.
	if (fabsf(relativeCenter.getX()) - sphere.radius > box.halfSize.getX() ||
		fabsf(relativeCenter.getY()) - sphere.radius > box.halfSize.getY() ||
		fabsf(relativeCenter.getZ()) - sphere.radius > box.halfSize.getZ())
	{
		return 0;
	}

	Vector3D closestPt(0, 0, 0);
	float dist;

	// Clamp each coordinate to the box.
	dist = relativeCenter.getX();
	if (dist > box.halfSize.getX()) dist = box.halfSize.getX();
	if (dist < -box.halfSize.getX()) dist = -box.halfSize.getX();
	closestPt.setX(dist);

	dist = relativeCenter.getY();
	if (dist > box.halfSize.getY()) dist = box.halfSize.getY();
	if (dist < -box.halfSize.getY()) dist = -box.halfSize.getY();
	closestPt.setY(dist);

	dist = relativeCenter.getZ();
	if (dist > box.halfSize.getZ()) dist = box.halfSize.getZ();
	if (dist < -box.halfSize.getZ()) dist = -box.halfSize.getZ();
	closestPt.setZ(dist);

	// Check we're in contact
	dist = (closestPt - relativeCenter).distance();
	if (dist > sphere.radius * sphere.radius) return 0;
	
	// Compile the contact
	Vector3D closestPtWorld = box.offset * closestPt;

	Contact* contact = new Contact();
	contact->rigidbodies.first = box.body;
	contact->rigidbodies.second = sphere.body;
	Vector3D normal = closestPtWorld - center;
	normal.setX(normal.getX() / normal.distance());
	normal.setY(normal.getY() / normal.distance());
	normal.setZ(normal.getZ() / normal.distance());
	contact->contactNormal = normal;
	contact->contactPoint = closestPtWorld;
	contact->penetration = sphere.radius - dist;
	contacts.push_back(*contact);


	return 1;
}

unsigned NarrowPhase::boxAndBox(const Box& firstBox, const Box& secondBox)
{
	return 0;
}
