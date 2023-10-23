
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include "Particules/Particule.h"
#include <iostream>
#include "Forces/ForceRegistry.h"
#include "Contact/ContactRegistry.h"
#include "Contact/LinkRegistry.h"

class PhysicEngine
{
public:
	static PhysicEngine* _physicengineptr ; 

	static PhysicEngine* GetInstance()
	{
		if (_physicengineptr == nullptr)
		{
			_physicengineptr = new PhysicEngine();
		}

		return _physicengineptr;
	}

	~PhysicEngine();

	void Delete() ;

	void Integrade(float DT);

	void Init() {};

	// --------------------------------------------------------------------------------
	void CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse, std::string name);
	Particule* GetParticule(std::string name);



	// --------------------------------------------------------------------------------
	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	
	LinkRegistry* GetLinkRegistry() { return &_linkregistry; }
private:

	std::map<std::string, Particule*> _physicobjects;

	ContactRegistry _contactregistry;
	ForceRegistry _forceregistry;
	LinkRegistry _linkregistry;
};

#endif

