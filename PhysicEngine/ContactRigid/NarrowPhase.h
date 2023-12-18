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

	bool endabledisplay = false;

	float transformToAxis(const Box& box,
		Vector3D& axis)
	{

		RigidCuboid* RBC = (RigidCuboid*)box.body;


		float x = RBC->getDX();
		float y = RBC->getDY();
		float z = RBC->getDZ();

		return
			x * abs(axis & RBC->getAxis(0)) +
			y * abs(axis & RBC->getAxis(1)) +
			z * abs(axis & RBC->getAxis(2));
	}
	
	
	bool overlapOnAxis(
		const Box& one,
		const Box& two,
		Vector3D& axis
	)
	{
		RigidCuboid* RBC0 = (RigidCuboid*)one.body;
		RigidCuboid* RBC1 = (RigidCuboid*)two.body;

		// Project the half-size of one onto axis.
		float oneProject = transformToAxis(one, axis);
		float twoProject = transformToAxis(two, axis);
		// Find the vector between the two centers.
		//Vector3D toCenter = RBC1->getAxis(3) - RBC0->getAxis(3);
		 Vector3D toCenter = RBC1->getPosition() - RBC0->getPosition();
		// Project this onto the axis.
		float distance = abs(toCenter & axis);
		// Check for overlap.

		Vector3D v = RBC1->getPosition() - RBC0->getPosition();
		
		/*
		std::cout << "_______________________\n";
		std::cout << "RBC0->getPosition()\t" << RBC0->getPosition().getX() << "\t" << RBC0->getPosition().getY() << "\t" << RBC0->getPosition().getZ() << "\n";
		std::cout << "RBC1->getPosition()\t" << RBC1->getPosition().getX() << "\t" << RBC1->getPosition().getY() << "\t" << RBC1->getPosition().getZ() << "\n";
		std::cout << "v\t" << v.getX() << "\t" << v.getY() << "\t" << v.getZ() << "\n";
		std::cout << "toCenter\t" << toCenter.getX() << "\t" << toCenter.getY() << "\t" << toCenter.getZ() << "\n";

		std::cout << "axe\t" << axis.getX() << "\t" << axis.getY() << "\t" << axis.getZ() << "\n";
		std::cout << "1\t" << oneProject << "\n";
		std::cout << "2\t" << twoProject << "\n";
		std::cout << "distance\t" << distance << "\n";

		std::cout << "_______________________\n";
		*/
		//std::cout << "distance\t" << distance << "\n";
		//std::cout << "oneProject + twoProject\t" << oneProject + twoProject << "\n";
		//std::cout << "\n";


		return (distance < oneProject + twoProject);
	}


	unsigned boxAndPoint(
		const Box& box,
		Vector3D& point,
		const Box& otherbox
	)
	{
		RigidCuboid* RBC = (RigidCuboid*)box.body;


		float x = RBC->getDX();
		float y = RBC->getDY();
		float z = RBC->getDZ();




		float newVal[9]
		{
			box.body->GettransformMatrix().getValues(0), box.body->GettransformMatrix().getValues(1), box.body->GettransformMatrix().getValues(2),
			box.body->GettransformMatrix().getValues(4), box.body->GettransformMatrix().getValues(5), box.body->GettransformMatrix().getValues(6),
			box.body->GettransformMatrix().getValues(8), box.body->GettransformMatrix().getValues(9), box.body->GettransformMatrix().getValues(10)
		};
		Matrice33 rotm(newVal);

		// Transform the point into box coordinates.
		Vector3D relPt = rotm * (point - box.body->getPosition());
		Vector3D normal;
		// Check each axis, looking for the axis on which the
			// penetration is least deep.
		
		float min_depth = x - abs(relPt.getX());
		if (min_depth < 0) return 0;
		normal = RBC->getAxis(0) * ((relPt.getX() < 0) ? -1 : 1);
		
		
		//std::cout << "y "<< y << "relPT,y "<< abs(relPt.getY()) << "\n";

		float depth = y - abs(relPt.getY());
		if (depth < 0) return 0;
		else if ((depth < min_depth && depth > 0) || min_depth == 0)
		{
			min_depth = depth;
			normal = RBC->getAxis(1) * ((relPt.getY() < 0) ? -1 : 1);
		}

		
		depth = z - abs(relPt.getZ());
		if (depth < 0) return 0;
		else if ((depth < min_depth && depth > 0) || min_depth == 0)
		{
			min_depth = depth;
			normal = RBC->getAxis(2) * ((relPt.getZ() < 0) ? -1 : 1);
		}

		
		// Compile the contact.
		Contact* contact = new Contact();
		contact->contactNormal = normal;
		contact->contactPoint = point;
		contact->penetration = min_depth;
		// Write the appropriate data.
		contact->rigidbodies.first = box.body;
		// Note that we don’t know what rigid body the point
		// belongs to, so we just use NULL. Where this is called
		// this value can be left, or filled in.
		contact->rigidbodies.second = otherbox.body;
		contact->restitution = 1;
		contact->friction = 1; 

		if (endabledisplay )
		{
			std::cout << "_______________________\n";

			//std::cout << "RBC->getAxis(0)\t" << RBC->getAxis(0).getX() << "\t" << RBC->getAxis(0).getY() << "\t" << RBC->getAxis(0).getZ() << "\n";
			//std::cout << "RBC->getAxis(1)\t" << RBC->getAxis(1).getX() << "\t" << RBC->getAxis(1).getY() << "\t" << RBC->getAxis(1).getZ() << "\n";
			//std::cout << "RBC->getAxis(2)\t" << RBC->getAxis(2).getX() << "\t" << RBC->getAxis(2).getY() << "\t" << RBC->getAxis(2).getZ() << "\n";
			//std::cout << "RBC0->getPosition()\t" << RBC->getPosition().getX() << "\t" << RBC->getPosition().getY() << "\t" << RBC->getPosition().getZ() << "\n";
			std::cout << "Box of point\t" << otherbox.body->getPosition().getX() << "\t" << otherbox.body->getPosition().getY() << "\t" << otherbox.body->getPosition().getZ() << "\n";
			std::cout << "point\t" << point.getX() << "\t" << point.getY() << "\t" << point.getZ() << "\n";
			std::cout << "penetration\t" << contact->penetration << "\n";

			std::cout << "_______________________\n";

		}

		
		
		
		contacts.push_back(*contact);
		//std::cout << "contact";

		return 1;
	}



	unsigned EdgeAndEdge(
		const Box& box,
		const Box& otherbox,
		Vector3D& point0,
		Vector3D& point1,
		Vector3D& axis0,
		Vector3D& axis1
	)
	{
		RigidCuboid* RBC = (RigidCuboid*)box.body;


		float x = RBC->getDX();
		float y = RBC->getDY();
		float z = RBC->getDZ();




		float newVal[9]
		{
			box.body->GettransformMatrix().getValues(0), box.body->GettransformMatrix().getValues(1), box.body->GettransformMatrix().getValues(2),
			box.body->GettransformMatrix().getValues(4), box.body->GettransformMatrix().getValues(5), box.body->GettransformMatrix().getValues(6),
			box.body->GettransformMatrix().getValues(8), box.body->GettransformMatrix().getValues(9), box.body->GettransformMatrix().getValues(10)
		};
		Matrice33 rotm(newVal);

		// Transform the point into box coordinates.
		Vector3D relPt = rotm * (point0 - box.body->getPosition());
		Vector3D normal;
		// Check each axis, looking for the axis on which the
			// penetration is least deep.

		float min_depth = x - abs(relPt.getX());
		if (min_depth < 0) return 0;
		normal = RBC->getAxis(0) * ((relPt.getX() < 0) ? -1 : 1);


		//std::cout << "y "<< y << "relPT,y "<< abs(relPt.getY()) << "\n";

		float depth = y - abs(relPt.getY());
		if (depth < 0) return 0;
		else if ((depth < min_depth && depth > 0) || min_depth == 0)
		{
			min_depth = depth;
			normal = RBC->getAxis(1) * ((relPt.getY() < 0) ? -1 : 1);
		}


		depth = z - abs(relPt.getZ());
		if (depth < 0) return 0;
		else if ((depth < min_depth && depth > 0) || min_depth == 0)
		{
			min_depth = depth;
			normal = RBC->getAxis(2) * ((relPt.getZ() < 0) ? -1 : 1);
		}


		// Compile the contact.
		Contact* contact = new Contact();
		contact->contactNormal = normal;
		contact->contactPoint = point0;
		contact->penetration = min_depth;
		// Write the appropriate data.
		contact->rigidbodies.first = box.body;
		// Note that we don’t know what rigid body the point
		// belongs to, so we just use NULL. Where this is called
		// this value can be left, or filled in.
		contact->rigidbodies.second = otherbox.body;
		contact->restitution = 1;
		contact->friction = 1;



		contacts.push_back(*contact);
		//std::cout << "contact";

		return 1;
	}





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