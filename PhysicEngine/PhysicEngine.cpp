#include "PhysicEngine.h"


PhysicEngine::~PhysicEngine()
{
	Delete();
}

void PhysicEngine::Delete()
{
	std::map<std::string, Particule*>::iterator it = _physicobjects.begin();
	while (it != _physicobjects.end())
	{
		delete(it->second);
		++it;
	}

	
}

void PhysicEngine::Integrade(float DTms)
{
	//std::cout << "start integrade\n";
	//apply all forces to all particules
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



	//_forceregistryRB.ApplyForces();

	std::map<std::string, RigidBody*>::iterator it2 = _physicobjectsRB.begin();

	while (it2 != _physicobjectsRB.end())
	{
		it2->second->integrade(DTms / 1000);
		++it2;
	}






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

}



// --------------------------------------------------------------------------------
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

// --------------------------------------------------------------------------------

void PhysicEngine::CreateRigidBody(float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	RigidBody* RB = new RigidBody(Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName);
	_physicobjectsRB.emplace(_ObjectName, RB);
	//_forceregistryRB.AddRigidBody(RB);
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
		//_forceregistryRB.RemoveRigidBody(name);
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
	//_forceregistryRB.AddRigidBody(RB);
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

void PhysicEngine::CreateRigidCuboid(float _DX, float _DY, float _DZ, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	RigidCuboid* RB = new RigidCuboid(_DX, _DY, _DZ, Masse, _position, _vitesse, _acceleration, _orientation, _rotation, _angularacceleration, _ObjectName);
	_physicobjectsRB.emplace(_ObjectName, RB);
	//_forceregistryRB.AddRigidBody(RB);
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
	//_forceregistryRB.AddRigidBody(RB);
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


ForceRegistry* PhysicEngine::GetForceRegistry() { return &_forceregistry; }