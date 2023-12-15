#include "NarrowPhase.h"

std::list<Contact> NarrowPhase::narrowPhase(std::list<RigidBody[2]> pairRigidbodies)
{
	Primitive firstPrimitive;
	Primitive secondPrimitive;
	for (auto pair : pairRigidbodies)
	{
		firstPrimitive.body = &pair[0];
		secondPrimitive.body = &pair[1];
		firstPrimitive.offset = pair[0].GettransformMatrix();
		secondPrimitive.offset = pair[1].GettransformMatrix();
		if (pair[0].getType() == TypeRigidBody::CUBOID)
		{
			if(pair[0].getIsStatic() == true)
				firstPrimitive.type = Primitive::PLANE;
			else if (pair[0].getIsStatic() == false)
			firstPrimitive.type = Primitive::BOX;
		}
		else if (pair[0].getType() == TypeRigidBody::SPHERE)
		{
			firstPrimitive.type = Primitive::SPHERE;
		}

		if (pair[1].getType() == TypeRigidBody::CUBOID)
		{
			secondPrimitive.type = Primitive::BOX;
		}
		else if (pair[1].getType() == TypeRigidBody::SPHERE)
		{
			secondPrimitive.type = Primitive::SPHERE;
		}

		generateContacts (firstPrimitive, secondPrimitive, nullptr);
	}
}

void NarrowPhase::generateContacts(const Primitive& firstPrimitive, const Primitive& secondPrimitive, CollisionData* data)
{
	if (firstPrimitive.body == nullptr || secondPrimitive.body == nullptr)
		return;
	if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::SPHERE)
	{
		sphereAndSphere((Sphere&)firstPrimitive, (Sphere&)secondPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::PLANE)
	{
		sphereAndHalfSpace((Sphere&)firstPrimitive, (Plane&)secondPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::PLANE && secondPrimitive.type == Primitive::SPHERE)
	{
		sphereAndHalfSpace((Sphere&)secondPrimitive, (Plane&)firstPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::PLANE)
	{
		boxPlane((Box&)firstPrimitive, (Plane&)secondPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::PLANE && secondPrimitive.type == Primitive::BOX)
	{
		boxPlane((Box&)secondPrimitive, (Plane&)firstPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::SPHERE)
	{
		boxAndSphere((Box&)firstPrimitive, (Sphere&)secondPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::SPHERE && secondPrimitive.type == Primitive::BOX)
	{
		boxAndSphere((Box&)secondPrimitive, (Sphere&)firstPrimitive, data);
	}
	else if (firstPrimitive.type == Primitive::BOX && secondPrimitive.type == Primitive::BOX)
	{
		boxAndBox((Box&)firstPrimitive, (Box&)secondPrimitive, data);
	}

}

unsigned NarrowPhase::sphereAndSphere(
	const Sphere& firstPrimitive,
	const Sphere& secondPrimitive,
	CollisionData* data) {
	if (data->contactsLeft == 0)
		return 0;

	Vector3D positionOne = firstPrimitive.body->getPosition();
	Vector3D positionTwo = secondPrimitive.body->getPosition();

	Vector3D midline = positionOne - positionTwo;
	float size = midline.distance();

	if(size <= 0.0f || size >= firstPrimitive.radius + secondPrimitive.radius)
		return 0;

	Vector3D normal = midline * (1.0f / size);

	Contact* contact = data->contacts;
	contact->rigidbodies[0] = *firstPrimitive.body;
	contact->rigidbodies[1] = *secondPrimitive.body;
	contact->contactNormal = normal;
	contact->contactPoint = positionOne + midline * 0.5f;
	contact->penetration = (firstPrimitive.radius + secondPrimitive.radius - size);
	contacts.push_back(*contact);
	return 1;
}

unsigned NarrowPhase::sphereAndHalfSpace(const Sphere& sphere, Plane& plane, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
	Vector3D positionOne = sphere.body->getPosition();
	
	float distance = (positionOne&plane.normal) - sphere.radius - plane.offset;

	if(distance >= 0.0f)
		return 0;
	//create the contact
	Contact* contact = data->contacts;
	contact->rigidbodies[0] = *sphere.body;
	contact->rigidbodies[1] = *plane.body;
	contact->contactNormal = plane.normal;
	contact->penetration = -distance;
	contact->contactPoint = positionOne - (plane.normal * (distance + sphere.radius));
	contacts.push_back(*contact);
	return 1;
}

unsigned NarrowPhase::boxPlane(const Box& box, const Plane& plane, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
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
			Contact* contact = data->contacts;
			contact->rigidbodies[0] = *box.body;
			contact->rigidbodies[1] = *plane.body;
			contact->contactNormal = plane.normal;
			contact->penetration = plane.offset - distance;
			contact->contactPoint = vertex[i];
			contacts.push_back(*contact);
		}
	}

	return 1;
}

unsigned NarrowPhase::boxAndSphere(const Box& box, const Sphere& sphere, CollisionData* data)
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

	Contact* contact = data->contacts;
	contact->rigidbodies[0] = *box.body;
	contact->rigidbodies[1] = *sphere.body;
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

unsigned NarrowPhase::boxAndBox(const Box& firstBox, const Box& secondBox, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
	return 0;
}
