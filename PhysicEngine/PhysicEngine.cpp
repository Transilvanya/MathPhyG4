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




	// Get an iterator pointing to the first element in the map
	std::map<std::string, Particule*>::iterator it = _physicobjects.begin();

	// Iterate through the map and print the elements
	while (it != _physicobjects.end())
	{
		it->second->integrade(DTms/1000);
		++it;
	}

	while (it != _physicobjects.end())
	{

	}
	_collisionRegistry.isColliding();



	//std::cout << "end integrade\n";
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


// --------------------------------------------------------------------------------
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


ForceRegistry* PhysicEngine::GetForceRegistry() { return &_forceregistry; }