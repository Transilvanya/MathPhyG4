#include "PhysicEngine.h"
#include "ContactRigid/NarrowPhase.h"
#include "ContactRigid/ContactSolverRigid.h"
#include "BSP/BSP.h"


PhysicEngine::~PhysicEngine()
{
	Delete();
}

void PhysicEngine::Delete()
{
	/*
	std::map<std::string, Particule*>::iterator it = _physicobjects.begin();
	while (it != _physicobjects.end())
	{
		delete(it->second);
		++it;
	}
	*/
	std::map<std::string, RigidBody*>::iterator it = _physicobjectsRB.begin();
	while (it != _physicobjectsRB.end())
	{
		delete(it->second);
		++it;
	}
}

void PhysicEngine::Integrade(float DTms)
{


	_forceregistryRB.ApplyForces();

	std::map<std::string, RigidBody*>::iterator it2 = _physicobjectsRB.begin();

	while (it2 != _physicobjectsRB.end())
	{
		it2->second->integrade(DTms / 1000);
		++it2;
	}

	NarrowPhase n;

	std::list<std::pair<RigidBody*, RigidBody*>> listbodies;

	vector<RigidBody*> bodies;

	std::map<std::string, RigidBody*>::iterator it = _physicobjectsRB.begin();

	//std::cout << "_____________________ objects\n";

	while (it != _physicobjectsRB.end())
	{
		bodies.push_back((it->second));
		
		std::map<std::string, RigidBody*>::iterator itt = it;
		itt++;
		while(itt != _physicobjectsRB.end())
		{
			listbodies.push_back(std::pair(it->second, itt->second));
			itt++;
		}
		it++;
	}

	BSP bsp(bodies);
	//listbodies = bsp.getPotentialCollision();

	listbodies = BroadPhase(listbodies);

	//std::cout << "_____________________ \n";

	std::vector<Contact> contacts = n.narrowPhase(listbodies);




	//return;




	ContactSolverRigid CSV;

	if (true)
	{
		//new contact detector WIP
		CSV.SolveContacts(contacts);
	}
	else
	{
		std::vector<Contact>::iterator itc = contacts.begin();
		/*
		if(contacts.size()!=0)
			std::cout << "______\n";
		while (itc != contacts.end())
		{

			std::cout <<"contactpoint\t" << itc->contactPoint.getX() << " " << itc->contactPoint.getY() << " " << itc->contactPoint.getZ() << "\n";
			std::cout <<"penetration\t" << itc->penetration << "\n";
			std::cout << "contactNormal\t" << itc->contactNormal.getX() << " " << itc->contactNormal.getY() << " " << itc->contactNormal.getZ() << "\n";
			std::cout << "\n";
			itc++;
		}
		if (contacts.size() != 0)
			std::cout << "______\n";
		*/
		/*
		std::vector<Contact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{
			it++;
		}
		*/

		int loopindex = 0;
		bool contactdetected = contacts.size() > 0;

		while (contactdetected && loopindex < 10)
		{

			std::vector<Contact>::iterator it = contacts.begin();
			Contact tempcontact = contacts.front();
			float maxpen = -1;

			while (it != contacts.end())
			{
				//std::cout << "pen " << it->penetration << " " << it->contactPoint.getX() << " " << it->contactPoint.getY() << " " << it->contactPoint.getZ() << "\n";

				if (it->penetration > maxpen)
				{
					maxpen = it->penetration;
					tempcontact = *it;
				}
				it++;
			}

			if (maxpen > 0.01)
			{
				//std::cout << "\n" << loopindex << " pen " << maxpen << "\t" << tempcontact.contactPoint.getX() << "\t" << tempcontact.contactPoint.getY() << "\t" << tempcontact.contactPoint.getZ() << "\n\n";


				//std::cout << "positionOne \t" << tempcontact.rigidbodies.first->getPosition().getX() << "\t" << tempcontact.rigidbodies.first->getPosition().getY() << "\t" << tempcontact.rigidbodies.first->getPosition().getZ() << "\n";
				//std::cout << "positionSecond \t" << tempcontact.rigidbodies.second->getPosition().getX() << "\t" << tempcontact.rigidbodies.second->getPosition().getY() << "\t" << tempcontact.rigidbodies.second->getPosition().getZ() << "\n";
				CSV.SolvePenetration(tempcontact);
				//std::cout << "positionOne \t" << tempcontact.rigidbodies.first->getPosition().getX() << "\t" << tempcontact.rigidbodies.first->getPosition().getY() << "\t" << tempcontact.rigidbodies.first->getPosition().getZ() << "\n";
				//std::cout << "positionSecond \t" << tempcontact.rigidbodies.second->getPosition().getX() << "\t" << tempcontact.rigidbodies.second->getPosition().getY() << "\t" << tempcontact.rigidbodies.second->getPosition().getZ() << "\n";

			}
			else
			{
				loopindex = 100;
			}



			contacts = n.narrowPhase(listbodies);
			contactdetected = contacts.size() > 0;

			//std::cout << contacts.size()<<"\n";

			loopindex++;
		}

		//if(loopindex!=0)
			//std::cout << "\n";

		contacts = n.narrowPhase(listbodies);

		itc = contacts.begin();
		/*
		if(contacts.size()!=0)
			std::cout << "______\n";
		while (itc != contacts.end())
		{

			std::cout <<"contactpoint\t" << itc->contactPoint.getX() << " " << itc->contactPoint.getY() << " " << itc->contactPoint.getZ() << "\n";
			std::cout <<"penetration\t" << itc->penetration << "\n";
			std::cout << "contactNormal\t" << itc->contactNormal.getX() << " " << itc->contactNormal.getY() << " " << itc->contactNormal.getZ() << "\n";
			std::cout << "\n";
			itc++;
		}
		if (contacts.size() != 0)
			std::cout << "______\n";
		*/
		/*
		std::vector<Contact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{
			it++;
		}
		*/

		loopindex = 0;
		contactdetected = contacts.size() > 0;

		//std::cout << "IMPULSION OFF\n";

		//loopindex = 10:

		while (contactdetected && loopindex < 10)
		{

			std::vector<Contact>::iterator it = contacts.begin();
			Contact tempcontact = contacts.front();
			Vector3D r0 = it->contactPoint - it->rigidbodies.first->getPosition();
			Vector3D r1 = it->contactPoint - it->rigidbodies.second->getPosition();
			Vector3D ObjectSpeed0 = it->rigidbodies.first->getVitesse() + it->rigidbodies.first->getRotation() * r0;
			Vector3D ObjectSpeed1 = it->rigidbodies.second->getVitesse() + it->rigidbodies.second->getRotation() * r1;
			float speeddif = (ObjectSpeed0 & it->contactNormal) - (ObjectSpeed1 & it->contactNormal);
			float max = speeddif;

			while (it != contacts.end())
			{
				r0 = it->contactPoint - it->rigidbodies.first->getPosition();
				r1 = it->contactPoint - it->rigidbodies.second->getPosition();
				ObjectSpeed0 = it->rigidbodies.first->getVitesse() + it->rigidbodies.first->getRotation() * r0;
				ObjectSpeed1 = it->rigidbodies.second->getVitesse() + it->rigidbodies.second->getRotation() * r1;
				speeddif = (ObjectSpeed0 & it->contactNormal) - (ObjectSpeed1 & it->contactNormal);
				//std::cout << "speeddif\t" << speeddif << "\n";

				if (speeddif > max)
				{
					max = speeddif;
					tempcontact = *it;
				}
				it++;
			}

			if (max > 0)
			{
				CSV.SolveImpulsion(tempcontact);
			}
			else
			{
				loopindex = 10;
			}

			contacts = n.narrowPhase(listbodies);
			contactdetected = contacts.size() > 0;
			loopindex++;
		}


	}
	

	

	/*
	int loopindex = 0;

	bool contactdetected = _contactregistry.AddContacts(_physicobjects);

	while (contactdetected && loopindex < 1)
	{
		//std::cout << "is contact " << _contactregistry.DetectContact(_physicobjects) << "\n";
//create list of contact
		//_contactregistry.DetectContact(_physicobjects);
		//move particule and apply impulsion
		_contactregistry.SolveContact();
		_contactregistry.ApplyAnchors();

		contactdetected = _contactregistry.AddContacts(_physicobjects);
		//std::cout << "end integrade\n";
		loopindex++;
	}//std::cout << "end integrade\n";

	_contactregistry.ApplyAnchors();
	*/






	/*
		//std::cout << "start integrade\n";
	//apply all forces to all rigidbodies
	_forceregistry.ApplyForces();

	//std::cout << "\n ______________________ Start PHY\n\n";

	// Get an iterator pointing to the first element in the map
	std::map<std::string, Particule*>::iterator it = _physicobjects.begin();

	// Iterate through the map and print the elements
	while (it != _physicobjects.end())
	{
		it->second->integrade(DTms/1000);

		//std::cout << it->second->GetName() << "\n";
		//std::cout << "\t\tposition " << it->second->getPosition().getX() << " " << it->second->getPosition().getY() << " " << it->second->getPosition().getZ() << "\n";
		//std::cout << "\t\tvitesse " << it->second->getVitesse().getX() << " " << it->second->getVitesse().getY() << " " << it->second->getVitesse().getZ() << "\n";

		++it;
	}
	//std::cout << "\n";



	int loopindex = 0;

	bool contactdetected = _contactregistry.AddContacts(_physicobjects);

	while (contactdetected && loopindex < 1)
	{
		//std::cout << "is contact " << _contactregistry.DetectContact(_physicobjects) << "\n";
//create list of contact
		//_contactregistry.DetectContact(_physicobjects);
		//move particule and apply impulsion
		_contactregistry.SolveContact();
		_contactregistry.ApplyAnchors();

		contactdetected = _contactregistry.AddContacts(_physicobjects);
		//std::cout << "end integrade\n";
		loopindex++;
	}//std::cout << "end integrade\n";

	_contactregistry.ApplyAnchors();
	*/
}



// --------------------------------------------------------------------------------
/*
void PhysicEngine::CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse , std::string name)
{
	Particule* PO = new Particule(newPosition, newVitesse, newAcceleration, masse, name);
	_physicobjects.emplace(name, PO);
	_forceregistry.AddParticule(PO);
}
Particule* PhysicEngine::GetParticule(std::string name)
{
	if (_physicobjects.count(name))
		return _physicobjects.find(name)->second;
	else
	{
		std::cout << "coud not get Object " << name << "\n";
		return nullptr;
	}
}


void PhysicEngine::RemoveParticule(std::string name)
{
	if (_physicobjects.count(name))
	{
		Particule* temp = _physicobjects.find(name)->second;
		_physicobjects.erase(name);
		_forceregistry.RemoveParticule(name);
		delete(temp);
	}
	else
	{
		std::cout << "coud not remove Object " << name << "\n";
	}
}

*/
// --------------------------------------------------------------------------------

void PhysicEngine::CreateRigidBody(float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	RigidBody* RB = new RigidBody(Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName);
	_physicobjectsRB.emplace(_ObjectName, RB);
	_forceregistryRB.AddRigidBody(RB);
}

RigidBody* PhysicEngine::GetRigidBody(std::string name)
{
	if (_physicobjectsRB.count(name))
		return _physicobjectsRB.find(name)->second;
	else
	{
		std::cout << "coud not get Object " << name << "\n";
		return nullptr;
	}
}
void PhysicEngine::RemoveRigidBody(std::string name)
{
	if (_physicobjectsRB.count(name))
	{
		RigidBody* temp = _physicobjectsRB.find(name)->second;
		_physicobjectsRB.erase(name);
		_forceregistryRB.RemoveRigidBody(name);
		delete(temp);
	}
	else
	{
		std::cout << "coud not remove Object " << name << "\n";
	}
}

void PhysicEngine::CreateRigidSphere(float _Radius, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	RigidSphere* RB = new RigidSphere(_Radius, Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName);
	_physicobjectsRB.emplace(_ObjectName, RB);
	_forceregistryRB.AddRigidBody(RB);
}
RigidSphere* PhysicEngine::GetRigidSphere(std::string name)
{
	if (_physicobjectsRB.count(name))
		return (RigidSphere*)_physicobjectsRB.find(name)->second;
	else
	{
		std::cout << "coud not get Object " << name << "\n";
		return nullptr;
	}
}

void PhysicEngine::CreateRigidCuboid(float _DX, float _DY, float _DZ, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName, bool _IsPlane)
{
	RigidCuboid* RB = new RigidCuboid(_DX, _DY, _DZ, Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName, _IsPlane);
	_physicobjectsRB.emplace(_ObjectName, RB);
	_forceregistryRB.AddRigidBody(RB);
}
RigidCuboid* PhysicEngine::GetRigidCuboid(std::string name)
{
	if (_physicobjectsRB.count(name))
		return (RigidCuboid*)_physicobjectsRB.find(name)->second;
	else
	{
		std::cout << "coud not get Object " << name << "\n";
		return nullptr;
	}
}

void PhysicEngine::CreateRigidCylinder(float _Radius, float _Height, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	RigidCylinder* RB = new RigidCylinder(_Radius, _Height, Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName);
	_physicobjectsRB.emplace(_ObjectName, RB);
	_forceregistryRB.AddRigidBody(RB);
}
RigidCylinder* PhysicEngine::GetRigidCylinder(std::string name)
{
	if (_physicobjectsRB.count(name))
		return (RigidCylinder*)_physicobjectsRB.find(name)->second;
	else
	{
		std::cout << "coud not get Object " << name << "\n";
		return nullptr;
	}
}
// --------------------------------------------------------------------------------


//ForceRegistry* PhysicEngine::GetForceRegistry() { return &_forceregistry; }
ForceRegistryRigid* PhysicEngine::GetForceRegistryRB() { return &_forceregistryRB; }


// ______________________


std::list<std::pair<RigidBody*, RigidBody*>> PhysicEngine::BroadPhase(std::list<std::pair<RigidBody*, RigidBody*>> listbodies)
{


	std::list<std::pair<RigidBody*, RigidBody*>> listbodies2 = listbodies;

	for (auto pairRB : listbodies)
	{
	
		float distance = (pairRB.first->getPosition() - pairRB.second->getPosition()).getNorm();
		//std::cout << "distance " << distance << "\n";

		int r0 = 0;
		int r1 = 0;

		if (pairRB.first->getType() == TypeRigidBody::CUBOID)
		{
			if (pairRB.first->getIsStatic() == true)
				r0 = 9999;
			else if (pairRB.first->getIsStatic() == false)
			{
				RigidCuboid* RBC = ((RigidCuboid*)pairRB.first);

				float x = RBC->getDX();
				float y = RBC->getDY();
				float z = RBC->getDZ();


				r0 = sqrt(x*x + y*y + z*z);
			}
				
		}
		else if (pairRB.first->getType() == TypeRigidBody::SPHERE)
		{
			r0 = ((RigidSphere*)pairRB.first)->getRadius();
		}


		if (pairRB.second->getType() == TypeRigidBody::CUBOID)
		{
			if (pairRB.second->getIsStatic() == true)
				r1 = 9999;
			else if (pairRB.second->getIsStatic() == false)
			{
				RigidCuboid* RBC = ((RigidCuboid*)pairRB.second);

				float x = RBC->getDX();
				float y = RBC->getDY();
				float z = RBC->getDZ();


				r1 = sqrt(x * x + y * y + z * z);
			}
		}

		else if (pairRB.second->getType() == TypeRigidBody::SPHERE)
		{
			r1 = ((RigidSphere*)pairRB.second)->getRadius();
		}

		//std::cout << "r0 " << r0 << "\n";
		//std::cout << "r1 " << r1 << "\n";

		if (distance > r0 + r1)
		{
			//std::cout << "removed\n";
			listbodies2.remove(pairRB);
		}
	}




	return listbodies2;
}
