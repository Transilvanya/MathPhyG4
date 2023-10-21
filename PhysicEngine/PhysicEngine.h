
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include "Particules/Particule.h"
#include <iostream>
#include "Forces/ForceRegistry.h"


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
	/*
	void CreateSphereObject(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, std::string _name, float _Radius)
	{
		SphereObject* SO = new SphereObject(newPosition, newVitesse, newAcceleration, _name, _Radius);
		_physicobjects.emplace(_name, SO);
		_forceregistry.AddPhyObject(SO);
		ElementToIntegrade.emplace(_name, SO);

	}
	
	SphereObject* GetSphereObject(std::string name)
	{

		if (_physicobjects.count(name) && _physicobjects.find(name)->second->getType() == 1)
			return (SphereObject*)_physicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get Sphere " << name << "\n";
			return nullptr;
		}

	}
	*/

	// --------------------------------------------------------------------------------
	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	

private:

	std::map<std::string, Particule*> _physicobjects;

	ForceRegistry _forceregistry;
	
};

#endif

