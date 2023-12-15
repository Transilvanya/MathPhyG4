#include "NarrowPhase.h"

NarrowPhase::NarrowPhase(std::list<std::array<RigidBody*, 2>> pairRigidbodies)
{
	CollisionData data = { 0 };
	data.contactsLeft = pairRigidbodies.size();
	while (data.contactsLeft != 0)
	{
		for (auto& pair : pairRigidbodies)
		{
			Primitive* firstPrimitive = new Primitive();
			Primitive* secondPrimitive = new Primitive();
			if (pair[0]->getType() == TypeRigidBody::CUBOID)
			{
				firstPrimitive->type = Primitive::BOX;
				firstPrimitive->body = (RigidCuboid*) &pair[0];
			}
			else if (pair[0]->getType() == TypeRigidBody::SPHERE)
			{
				firstPrimitive->type = Primitive::SPHERE;
				firstPrimitive->body = pair[0];
			}

			if (pair[1]->getType() == TypeRigidBody::CUBOID)
			{
				secondPrimitive->type = Primitive::BOX;
				secondPrimitive->body = (RigidCuboid*) &pair[1];
			}
			else if (pair[1]->getType() == TypeRigidBody::SPHERE)
			{
				secondPrimitive->type = Primitive::SPHERE;
				secondPrimitive->body = pair[1];
			}

			firstPrimitive->offset = pair[0]->GettransformMatrix();
			secondPrimitive->offset = pair[1]->GettransformMatrix();
			printf("firstPrimitive.type : %d\n", pair[0]->getType());
			printf("secondPrimitive.type : %d\n", pair[1]->getType());
			

			generateContacts(firstPrimitive,secondPrimitive, &data);
		}
		data.contactsLeft--;
	}
}

void NarrowPhase::generateContacts(const Primitive* firstPrimitive, const Primitive* secondPrimitive, CollisionData* data)
{
	if (firstPrimitive->body == nullptr || secondPrimitive->body == nullptr)
		return;
	if (firstPrimitive->type == Primitive::SPHERE && secondPrimitive->type == Primitive::SPHERE)
	{
		sphereAndSphere((Sphere*)firstPrimitive, (Sphere*)secondPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::SPHERE && secondPrimitive->type == Primitive::PLANE)
	{
		sphereAndHalfSpace((Sphere*)firstPrimitive, (Plane*)secondPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::PLANE && secondPrimitive->type == Primitive::SPHERE)
	{
		sphereAndHalfSpace((Sphere*)secondPrimitive, (Plane*)firstPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::BOX && secondPrimitive->type == Primitive::PLANE)
	{
		boxPlane((Box*)firstPrimitive, (Plane*)secondPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::PLANE && secondPrimitive->type == Primitive::BOX)
	{
		boxPlane((Box*)secondPrimitive, (Plane*)firstPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::BOX && secondPrimitive->type == Primitive::SPHERE)
	{
		boxAndSphere((Box*)firstPrimitive, (Sphere*)secondPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::SPHERE && secondPrimitive->type == Primitive::BOX)
	{
		boxAndSphere((Box*)secondPrimitive, (Sphere*)firstPrimitive, data);
	}
	else if (firstPrimitive->type == Primitive::BOX && secondPrimitive->type == Primitive::BOX)
	{
		boxAndBox((Box*)firstPrimitive, (Box*)secondPrimitive, data);
	}

}

unsigned NarrowPhase::sphereAndSphere(
	Sphere* sphere1,
	Sphere* sphere2,
	CollisionData* data) {
	if (data->contactsLeft == 0)
		return 0;

	Vector3D positionOne = sphere1->body->getPosition();
	Vector3D positionTwo = sphere2->body->getPosition();
	sphere1->radius = ((RigidSphere*) sphere1->body)->getRadius();
	sphere2->radius = ((RigidSphere*) sphere2->body)->getRadius();

	Vector3D midline = positionOne - positionTwo;
	float size = midline.distance();

	if(size <= 0.0f || size >= sphere1->radius + sphere2->radius)
		return 0;

	Vector3D normal = midline * (1.0f / size);

	std::array<RigidBody*, 2> rigidbodiesBis = { sphere1->body, sphere2->body };
	Contact contact = Contact(positionOne + midline * 0.5f, normal, (sphere1->radius + sphere2->radius - size), 0,0, rigidbodiesBis);
	contacts.push_back(&contact);
	printf("sphereAndSphere\n");
	return 1;
}

unsigned NarrowPhase::sphereAndHalfSpace(Sphere* sphere, Plane* plane, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
	Vector3D positionOne = sphere->body->getPosition();
	
	float distance = (positionOne&plane->normal) - sphere->radius - plane->offset;

	if(distance >= 0.0f)
		return 0;
	//create the contact
	Contact* contact = data->contacts;
	contact->rigidbodies[0] = sphere->body;
	contact->rigidbodies[1] = plane->body;
	contact->contactNormal = plane->normal;
	contact->penetration = -distance;
	contact->contactPoint = positionOne - (plane->normal * (distance + sphere->radius));
	contacts.push_back(contact);
	return 1;
}

unsigned NarrowPhase::boxPlane(Box* box, Plane* plane, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
	Vector3D vertex[8] = {
		Vector3D(-box->halfSize.getX(), -box->halfSize.getY(),-box->halfSize.getZ()),
		Vector3D(-box->halfSize.getX(), -box->halfSize.getY(), box->halfSize.getZ()),
		Vector3D(-box->halfSize.getX(), box->halfSize.getY(), -box->halfSize.getZ()),
		Vector3D(-box->halfSize.getX(), box->halfSize.getY(), box->halfSize.getZ()),
		Vector3D(box->halfSize.getX(), -box->halfSize.getY(), -box->halfSize.getZ()),
		Vector3D(box->halfSize.getX(), -box->halfSize.getY(), box->halfSize.getZ()),
		Vector3D(box->halfSize.getX(), box->halfSize.getY(), -box->halfSize.getZ()),
		Vector3D(box->halfSize.getX(), box->halfSize.getY(), box->halfSize.getZ())
	};

	for (int i = 0; i < 8; i++)
	{
		vertex[i] = box->offset * vertex[i];
	}

	for (int i = 0; i < 8; i++)
	{
		float distance = vertex[i] & plane->normal;
		if (distance <= plane->offset)
		{
			Contact* contact = data->contacts;
			contact->rigidbodies[0] = box->body;
			contact->rigidbodies[1] = plane->body;
			contact->contactNormal = plane->normal;
			contact->penetration = plane->offset - distance;
			contact->contactPoint = vertex[i];
			contacts.push_back(contact);
		}
	}

	return 1;
}

unsigned NarrowPhase::boxAndSphere(Box* box, Sphere* sphere, CollisionData* data)
{
	Vector3D center = sphere->body->getPosition();
	Vector3D relativeCenter = box->offset * center;
	sphere->radius = ((RigidSphere*)sphere->body)->getRadius();
	Vector3D halfSize = Vector3D(((RigidCuboid*)box->body)->getDX()/2, ((RigidCuboid*)box->body)->getDY() / 2, ((RigidCuboid*)box->body)->getDZ() / 2);
	box->halfSize = halfSize;


	// Early-out check to see if we can exclude the contact.
	if (fabsf(relativeCenter.getX()) - sphere->radius > box->halfSize.getX() ||
		fabsf(relativeCenter.getY()) - sphere->radius > box->halfSize.getY() ||
		fabsf(relativeCenter.getZ()) - sphere->radius > box->halfSize.getZ())
	{
		return 0;
	}

	Vector3D closestPt(0, 0, 0);
	float dist;

	// Clamp each coordinate to the box->
	dist = relativeCenter.getX();
	if (dist > box->halfSize.getX()) dist = box->halfSize.getX();
	if (dist < -box->halfSize.getX()) dist = -box->halfSize.getX();
	closestPt.setX(dist);

	dist = relativeCenter.getY();
	if (dist > box->halfSize.getY()) dist = box->halfSize.getY();
	if (dist < -box->halfSize.getY()) dist = -box->halfSize.getY();
	closestPt.setY(dist);

	dist = relativeCenter.getZ();
	if (dist > box->halfSize.getZ()) dist = box->halfSize.getZ();
	if (dist < -box->halfSize.getZ()) dist = -box->halfSize.getZ();
	closestPt.setZ(dist);

	// Check we're in contact
	dist = (closestPt - relativeCenter).distance();
	if (dist > sphere->radius * sphere->radius) return 0;
	
	// Compile the contact
	Vector3D closestPtWorld = box->offset * closestPt;

	Contact* contact = data->contacts;
	contact->rigidbodies[0] = box->body;
	contact->rigidbodies[1] = sphere->body;
	Vector3D normal = closestPtWorld - center;
	normal.setX(normal.getX() / normal.distance());
	normal.setY(normal.getY() / normal.distance());
	normal.setZ(normal.getZ() / normal.distance());
	contact->contactNormal = normal;
	contact->contactPoint = closestPtWorld;
	contact->penetration = sphere->radius - dist;
	contacts.push_back(contact);
	printf("boxAndSphere\n");
	return 1;
}

unsigned NarrowPhase::boxAndBox(Box* firstBox, Box* secondBox, CollisionData* data)
{
	if(data->contactsLeft == 0)
		return 0;
	return 0;
}
