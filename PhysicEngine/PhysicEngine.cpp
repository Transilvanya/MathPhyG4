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

		it->second->getVitesse();

		it->second->integrade(DTms/1000);
		++it;
	}

	int loopindex = 0;

	bool contactdetected = _contactregistry.DetectContact(_physicobjects);

	while (contactdetected && loopindex < 10)
	{
		//std::cout << "is contact " << _contactregistry.DetectContact(_physicobjects) << "\n";
//create list of contact
		//_contactregistry.DetectContact(_physicobjects);
		//move particule and apply impulsion
		_contactregistry.SolveContact();

		//move particule according to the links
		_linkregistry.SolveLink();

		contactdetected = _contactregistry.DetectContact(_physicobjects);
		//std::cout << "end integrade\n";
		loopindex++;
	}//std::cout << "end integrade\n";
	

	_linkregistry.SolveLink();
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