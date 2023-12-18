#include "NarrowPhase.h"

std::vector<Contact> NarrowPhase::narrowPhase(std::list<std::pair<RigidBody*, RigidBody*> > pairRigidbodies)
{
	Primitive firstPrimitive;
	Primitive secondPrimitive;

	contacts.clear();

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
			if (pair.second->getIsStatic() == true)
				secondPrimitive.type = Primitive::PLANE;
			else if (pair.second->getIsStatic() == false)
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


//validate
unsigned NarrowPhase::sphereAndSphere(
	const Sphere& firstPrimitive,
	const Sphere& secondPrimitive) {

	

	Vector3D positionOne = firstPrimitive.body->getPosition();
	Vector3D positionTwo = secondPrimitive.body->getPosition();

	Vector3D midline = positionTwo -  positionOne;
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

//done
unsigned NarrowPhase::sphereAndHalfSpace(const Sphere& sphere, Plane& plane)
{
	Vector3D positionOne = sphere.body->getPosition();
	

	Vector3D PlaneNormal = ((RigidCuboid*)plane.body)->getNormal(); //validé
	Quaternion PlanQt = ((RigidCuboid*)plane.body)->getOrientation();

	float offset = ((RigidCuboid*)plane.body)->getOffset();
	
	positionOne = positionOne - Vector3D(0, offset, 0); // if gety > 0 work

	if (PlaneNormal.getY() < 0)
			offset = -offset;

//	std::cout << "\n";

	//std::cout << "norm normal\t" << PlaneNormal.getNorm() << "\n";
	//std::cout << "positionOne \t" << positionOne.getX() << "\t" << positionOne.getY() << "\t" << positionOne.getZ() << "\n";
	//std::cout << "PlaneNormal \t" << PlaneNormal.getX() << "\t" << PlaneNormal.getY() << "\t" << PlaneNormal.getZ() << "\n";
	//std::cout << "PlaneORientation \t" << PlanQt.getW() << "\t" << PlanQt.getX() << "\t" << PlanQt.getY() << "\t" << PlanQt.getZ() << "\n";
	//std::cout << "Offset\t" << ((RigidCuboid*)plane.body)->getOffset() << "\n";
	//std::cout << "distance to axe\t" << (positionOne & PlaneNormal) << "\n";

	float distancecentresphere = (positionOne& PlaneNormal) - ((RigidSphere*)sphere.body)->getRadius();

//	std::cout << "distance\t" << distancecentresphere << "\n";

	if(distancecentresphere >= 0.0f)
		return 0;
	//create the contact

	Contact* contact = new Contact();
	contact->rigidbodies.first = plane.body;
	contact->rigidbodies.second = sphere.body;
	contact->contactNormal = PlaneNormal;
	contact->penetration = -distancecentresphere;
	contact->restitution = 1;
	contact->contactPoint = sphere.body->getPosition() - (PlaneNormal * ((RigidSphere*)sphere.body)->getRadius());
	contacts.push_back(*contact);
	return 1;
}

//done
unsigned NarrowPhase::boxPlane(const Box& box, const Plane& plane)
{


	RigidCuboid* RBC = (RigidCuboid*) box.body;


	float x = RBC->getDX();
	float y = RBC->getDY();
	float z = RBC->getDZ();

	Vector3D RBCPos = RBC->getPosition();



	float newVal[9]
	{
		RBC->GettransformMatrix().getValues(0), RBC->GettransformMatrix().getValues(1), RBC->GettransformMatrix().getValues(2),
		RBC->GettransformMatrix().getValues(4), RBC->GettransformMatrix().getValues(5), RBC->GettransformMatrix().getValues(6),
		RBC->GettransformMatrix().getValues(8), RBC->GettransformMatrix().getValues(9), RBC->GettransformMatrix().getValues(10)
	};
	Matrice33 m(newVal);

	Vector3D listpoints[8] =
	{
		(m*Vector3D(x , y, z) + RBCPos),
		(m*Vector3D(x , y, -z) + RBCPos),

		(m*Vector3D(x , -y, z) + RBCPos),
		(m*Vector3D(x , -y, -z) + RBCPos),


		(m*Vector3D(-x ,y , z) + RBCPos),
		(m*Vector3D(-x ,y , -z) + RBCPos),

		(m*Vector3D(-x ,-y , z) + RBCPos),
		(m*Vector3D(-x ,-y , -z) + RBCPos)
	};
		
	for (int i = 0; i < 8; i++)
	{




		Vector3D positionOne = listpoints[i];//sphere.body->getPosition();
		Vector3D PlaneNormal = ((RigidCuboid*)plane.body)->getNormal();
		float offset = ((RigidCuboid*)plane.body)->getOffset();
		positionOne = positionOne - Vector3D(0, offset, 0); // if gety > 0 work

		if (PlaneNormal.getY() < 0)
			offset = -offset;

		float distancecentresphere = (positionOne & PlaneNormal);

		//std::cout << "distance to axe\t" << (positionOne & PlaneNormal) << "\n";

		if (distancecentresphere < 0.0f)
		{
			//create the contact

			Contact* contact = new Contact();
			contact->rigidbodies.first = plane.body;
			contact->rigidbodies.second = box.body ;
			contact->contactNormal = PlaneNormal;
			contact->penetration = -distancecentresphere ;
			contact->restitution = 0;
			contact->contactPoint = listpoints[i];

		//	std::cout << "positionBox \t" << RBC->getPosition().getX() << "\t" << RBC->getPosition().getY() << "\t" << RBC->getPosition().getZ() << "\n";
		//std::cout << "positionOne \t" << listpoints[i].getX() << "\t" << listpoints[i].getY() << "\t" << listpoints[i].getZ() << "\n";

		//	std::cout << "pen \t" << contact->penetration << "\n";
		//	std::cout << "normal \t" << PlaneNormal.getX() << "\t" << PlaneNormal.getY() << "\t" << PlaneNormal.getZ() << "\n";

			contacts.push_back(*contact);
		}
	}


	//if (contacts.size() != 0)
	//	std::cout <<"\n";

	return 1;
}

//to do
unsigned NarrowPhase::boxAndSphere(const Box& box, const Sphere& sphere)
{
	/*
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


*/






	RigidCuboid* BoxRB = (RigidCuboid*)box.body;
	RigidSphere* SphRB = (RigidSphere*)sphere.body;

	float x = BoxRB->getDX();
	float y = BoxRB->getDY();
	float z = BoxRB->getDZ();

	Vector3D RBCPos = BoxRB->getPosition();

	//change 6 and 9 due to coordiante change
	float newVal[9]
	{
		BoxRB->GettransformMatrix().getValues(0), BoxRB->GettransformMatrix().getValues(1), BoxRB->GettransformMatrix().getValues(2),
		BoxRB->GettransformMatrix().getValues(4), BoxRB->GettransformMatrix().getValues(5), BoxRB->GettransformMatrix().getValues(9),
		BoxRB->GettransformMatrix().getValues(8), BoxRB->GettransformMatrix().getValues(6), BoxRB->GettransformMatrix().getValues(10)
	};

	Matrice33 RotBox(newVal);

	Vector3D listpoints[8] =
	{
		(Vector3D(x , y, z)),
		(Vector3D(x , y, -z)),
		(Vector3D(x , -y, z)),
		(Vector3D(x , -y, -z)),
		(Vector3D(-x ,y , z)),
		(Vector3D(-x ,y , -z)),
		(Vector3D(-x ,-y , z)),
		(Vector3D(-x ,-y , -z))
	};

	Vector3D listpoints2[8] =
	{
		RotBox * (Vector3D(x , y, z)),
		RotBox * (Vector3D(x , y, -z)),
		RotBox * (Vector3D(x , -y, z)),
		RotBox * (Vector3D(x , -y, -z)),
		RotBox * (Vector3D(-x ,y , z)),
		RotBox * (Vector3D(-x ,y , -z)),
		RotBox * (Vector3D(-x ,-y , z)),
		RotBox * (Vector3D(-x ,-y , -z))
	};

	Vector3D relCenter = RotBox * (SphRB->getPosition() - RBCPos);

	
	// Early-out check to see if we can exclude the contact.
	if (abs(relCenter.getX()) - SphRB->getRadius() > x ||
		abs(relCenter.getY()) - SphRB->getRadius() > y ||
		abs(relCenter.getZ()) - SphRB->getRadius() > z)
	{
		return 0;
	}

	Vector3D closestPt(0, 0, 0);

	// Clamp each coordinate to the box.
	float	dist = relCenter.getX();
	if (dist > x) dist = x;
	if (dist < -x) dist = -x;
	closestPt.setX(dist);

	dist = relCenter.getY();
	if (dist > y) dist = y;
	if (dist < -y) dist = -y;
	closestPt.setY(dist);

	dist = relCenter.getZ();
	if (dist > z) dist = z;
	if (dist < -z) dist = -z;
	closestPt.setZ(dist);

	

	Vector3D tempvect = (closestPt - relCenter);
	// Check we’re in contact.
	dist = tempvect.getX() * tempvect.getX() + tempvect.getY() * tempvect.getY() + tempvect.getZ() * tempvect.getZ();

	if (dist > SphRB->getRadius() * SphRB->getRadius()) return 0;

	//Compile the contact.
	Vector3D closestPtWorld = RotBox.Inverse() * closestPt + RBCPos;
	Contact* contact = new Contact();

	//contact->contactNormal = (RBS->getPosition() - closestPtWorld);
	
	Vector3D normal = SphRB->getPosition() - closestPtWorld;

	
	Vector3D normalRelat = relCenter - closestPt;


	std::cout << "relCenter\t" << relCenter.getX() << " " << relCenter.getY() << " " << relCenter.getZ() << "\n";
	std::cout << "Sph Position\t" << SphRB->getPosition().getX() << " " << SphRB->getPosition().getY() << " " << SphRB->getPosition().getZ() << "\n\n";

	std::cout << "closestPt\t" << closestPt.getX() << " " << closestPt.getY() << " " << closestPt.getZ() << "\n";
	std::cout << "closestPtWorld\t" << closestPtWorld.getX() << " " << closestPtWorld.getY() << " " << closestPtWorld.getZ() << "\n\n";

	std::cout << "RBCPos\t" << RBCPos.getX() << " " << RBCPos.getY() << " " << RBCPos.getZ() << "\n";

	
	

	std::cout << "\n";

	std::cout << "normalRelat\t" << normalRelat.getX() << " " << normalRelat.getY() << " " << normalRelat.getZ() << "\n";
	normalRelat = RotBox.Inverse() * normalRelat;
	std::cout << "normalRelat\t" << normalRelat.getX() << " " << normalRelat.getY() << " " << normalRelat.getZ() << "\n";
	std::cout << "normal\t" << normal.getX() << " " << normal.getY() << " " << normal.getZ() << "\n";
	
	

	normal.setX(normal.getX() / normal.distance());
	normal.setY(normal.getY() / normal.distance());
	normal.setZ(normal.getZ() / normal.distance());
	contact->contactNormal = normal;
	
	contact->contactPoint = closestPtWorld;
	contact->penetration = SphRB->getRadius() - sqrt(dist);
	// Write the appropriate data.
	contact->rigidbodies.first = box.body;
	contact->rigidbodies.second = sphere.body;
	contact->restitution = 1;
	contact->friction = 1;

//	std::cout << "pen \t" << contact->penetration << "\n";
//std::cout << "normal \t" << normal.getX() << "\t" << normal.getY() << "\t" << normal.getZ() << "\n";
//	std::cout << "contact \t" << closestPtWorld.getX() << "\t" << closestPtWorld.getY() << "\t" << closestPtWorld.getZ() << "\n";
//std::cout << " RBS->getPosition() \t" << RBS->getPosition().getX() << "\t" << RBS->getPosition().getY() << "\t" << RBS->getPosition().getZ() << "\n";
//	std::cout << " RBC->getPosition() \t" << RBC->getPosition().getX() << "\t" << RBC->getPosition().getY() << "\t" << RBC->getPosition().getZ() << "\n";

	contacts.push_back(*contact);


	return 1;
}

//to do
unsigned NarrowPhase::boxAndBox(const Box& firstBox, const Box& secondBox)
{

	RigidCuboid* RBC0 = (RigidCuboid*)firstBox.body;
	RigidCuboid* RBC1 = (RigidCuboid*)secondBox.body;


	float x0 = RBC0->getDX();
	float y0 = RBC0->getDY();
	float z0 = RBC0->getDZ();

	Vector3D RBCPos0 = RBC0->getPosition();


	//6 and 9 inverted du to a change in coordinate beetwen graphic engine and physic engine
	float newVal0[9]
	{
		RBC0->GettransformMatrix().getValues(0), RBC0->GettransformMatrix().getValues(1), -RBC0->GettransformMatrix().getValues(2),
		RBC0->GettransformMatrix().getValues(4), RBC0->GettransformMatrix().getValues(5), -RBC0->GettransformMatrix().getValues(9),
		RBC0->GettransformMatrix().getValues(8), RBC0->GettransformMatrix().getValues(6), -RBC0->GettransformMatrix().getValues(10)
	};
	Matrice33 m0(newVal0);

	Vector3D listpoints0[8] =
	{
		(m0 * Vector3D(x0 , y0, z0) + RBCPos0),
		(m0 * Vector3D(x0 , y0, -z0) + RBCPos0),
		
		(m0 * Vector3D(x0 , -y0, z0) + RBCPos0),
		(m0 * Vector3D(x0 , -y0, -z0) + RBCPos0),


		(m0 * Vector3D(-x0 ,y0 , z0) + RBCPos0),
		(m0 * Vector3D(-x0 ,y0 , -z0) + RBCPos0),

		(m0 * Vector3D(-x0 ,-y0 , z0) + RBCPos0),
		(m0 * Vector3D(-x0 ,-y0 , -z0) + RBCPos0)
	};

	float x = RBC1->getDX();
	float y = RBC1->getDY();
	float z = RBC1->getDZ();

	Vector3D RBCPos1 = RBC1->getPosition();

	float newVal1[9]
	{
		RBC1->GettransformMatrix().getValues(0), RBC1->GettransformMatrix().getValues(1), RBC1->GettransformMatrix().getValues(2),
		RBC1->GettransformMatrix().getValues(4), RBC1->GettransformMatrix().getValues(5), RBC1->GettransformMatrix().getValues(9),
		RBC1->GettransformMatrix().getValues(8), RBC1->GettransformMatrix().getValues(6), RBC1->GettransformMatrix().getValues(10)
	};

	/*
			RBC1->GettransformMatrix().getValues(0), RBC1->GettransformMatrix().getValues(1), RBC1->GettransformMatrix().getValues(2),
		RBC1->GettransformMatrix().getValues(4), RBC1->GettransformMatrix().getValues(5), RBC1->GettransformMatrix().getValues(6),
		RBC1->GettransformMatrix().getValues(8), RBC1->GettransformMatrix().getValues(9), RBC1->GettransformMatrix().getValues(10)
	*/
	Matrice33 m1(newVal1);

	//std::cout << m1.getValues(0) << "\t" << m1.getValues(1) << "\t" << m1.getValues(2) << "\n";
	//std::cout << m1.getValues(3) << "\t" << m1.getValues(4) << "\t" << m1.getValues(5) << "\n";
	//std::cout << m1.getValues(6) << "\t" << m1.getValues(7) << "\t" << m1.getValues(8) << "\n\n";



	Vector3D listpoints1[8] =
	{

		(m1 * Vector3D(x , y, z) + RBCPos1),
		(m1 * Vector3D(x , -y, z) + RBCPos1),

		(m1 * Vector3D(x , y, -z) + RBCPos1),
		(m1 * Vector3D(x , -y, -z) + RBCPos1),

		(m1 * Vector3D(-x ,y , z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , z) + RBCPos1),

		(m1 * Vector3D(-x ,y , -z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , -z) + RBCPos1),

		/*
		(m1 * Vector3D(x , y, z) + RBCPos1),
		(m1 * Vector3D(x , -y, z) + RBCPos1),
		
		(m1 * Vector3D(-x ,y , z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , z) + RBCPos1),

		(m1 * Vector3D(x , y, -z) + RBCPos1),
		(m1 * Vector3D(x , -y, -z) + RBCPos1),

		(m1 * Vector3D(-x ,y , -z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , -z) + RBCPos1),
		*/
		
		/*
		(m1 * Vector3D(x , y, z) + RBCPos1),
		(m1 * Vector3D(-x ,y , z) + RBCPos1),
		(m1 * Vector3D(x , y, -z) + RBCPos1),
		(m1 * Vector3D(-x ,y , -z) + RBCPos1),
		

		(m1 * Vector3D(x , -y, z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , z) + RBCPos1),
		(m1 * Vector3D(x , -y, -z) + RBCPos1),
		(m1 * Vector3D(-x ,-y , -z) + RBCPos1),
		*/
	};

	//std::cout << "\n";
	for (int i = 0; i < 4; i++)
	{
	//	std::cout << "listpoints1\t" << listpoints1[i].getX() << "\t" << listpoints1[i].getY() << "\t" << listpoints1[i].getZ() << "\n";
	}




	Vector3D v[15];
	v[0] = RBC0->getAxis(0);
	v[1] = RBC0->getAxis(1);
	v[2] = RBC0->getAxis(2);

	v[3] = RBC1->getAxis(0);
	v[4] = RBC1->getAxis(1);
	v[5] = RBC1->getAxis(2);


	v[6] = RBC0->getAxis(0) * RBC1->getAxis(0);
	v[7] = RBC0->getAxis(0) * RBC1->getAxis(1);
	v[8] = RBC0->getAxis(0) * RBC1->getAxis(2);

	v[9] = RBC0->getAxis(1) * RBC1->getAxis(0);
	v[10] = RBC0->getAxis(1) * RBC1->getAxis(1);
	v[11] = RBC0->getAxis(1) * RBC1->getAxis(2);

	v[12] = RBC0->getAxis(2) * RBC1->getAxis(0);
	v[13] = RBC0->getAxis(2) * RBC1->getAxis(1);
	v[14] = RBC0->getAxis(2) * RBC1->getAxis(2);


	for (int i = 0; i < 5; i++)
	{
		//std::cout << "v" << i * 3 + 0 << "\t" << v[i * 3 + 0].getX() << "\t" << v[i * 3 + 0].getY() << "\t" << v[i * 3 + 0].getZ() << "\n";
		//std::cout << "v" << i * 3 + 1 << "\t" << v[i * 3 + 1].getX() << "\t" << v[i * 3 + 1].getY() << "\t" << v[i * 3 + 1].getZ() << "\n";
		//std::cout << "v" << i * 3 + 2 << "\t" << v[i * 3 + 2].getX() << "\t" << v[i * 3 + 2].getY() << "\t" << v[i * 3 + 2].getZ() << "\n\n";
		
	
	}
	//std::cout << "\n\n";

	
	int sum = 0;
	for (int i = 0; i < 15; i++)
	{
		sum += overlapOnAxis(firstBox, secondBox, v[i]);
	//	std::cout << "overlap " << overlapOnAxis(firstBox, secondBox, v[i]) << "\n";
	}
	//std::cout << sum << "\n";

	//Check SAT
	if (sum == 0)
		return 0;
	
	

	//Check for Pont Face

	//std::cout << "\t\tstart \n";
	for (int i = 0; i < 8; i++)
	{
		//std::cout << "listpoints0\t" << listpoints0[i].getX() << "\t" << listpoints0[i].getY() << "\t" << listpoints0[i].getZ() << "\n";
	boxAndPoint(secondBox, listpoints0[i], firstBox);
	//std::cout << boxAndPoint(secondBox, listpoints0[i], firstBox) << "\n";
	}
	//std::cout << "\t\tmid\n";
	//std::cout << "\n";
	for (int i = 0; i < 8; i++)
	{
		//std::cout << "listpoints1\t" << listpoints1[i].getX() << "\t" << listpoints1[i].getY() << "\t" << listpoints1[i].getZ() << "\n";
		//std::cout << boxAndPoint(firstBox, listpoints1[i], secondBox) << "\n";
		boxAndPoint(firstBox, listpoints1[i], secondBox);
	}

	//std::cout << "\t\tend\n";
	


	//Check for Edge Edge

	// normal contact is produit vection des deux axes a * b,
	// interpenetration is distance entre 2 axe


	return 1;
}
