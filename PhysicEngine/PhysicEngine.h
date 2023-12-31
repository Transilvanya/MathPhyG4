
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include <iostream>

/*
#include "Particules/Particule.h"
#include "Forces/ForceRegistry.h"
#include "Contact/ContactRegistry.h"
*/

#include "vector/Vector3D.h"
#include "Matrices/Matrice33.h"
#include "RigidBody/RigidBody.h"
#include "ForceRigid/ForceRegistryRigid.h"

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

	void CreateRigidBody(float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName);
	RigidBody* GetRigidBody(std::string name);
	void RemoveRigidBody(std::string name);

	//call CreateRigidBody with the correct Tenseur and type
	void CreateRigidSphere(float _Radius, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName);
	RigidSphere* GetRigidSphere(std::string name);

	void CreateRigidCuboid(float _DX, float _DY, float _DZ, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName, bool _IsPlane);
	RigidCuboid* GetRigidCuboid(std::string name);

	void CreateRigidCylinder(float _Radius, float _Height, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName);
	RigidCylinder* GetRigidCylinder(std::string name);


	ForceRegistryRigid* GetForceRegistryRB();



	void UpdateObjects()
	{

		std::map<std::string, RigidBody*>::iterator it2 = _physicobjectsRB.begin();

		while (it2 != _physicobjectsRB.end())
		{
			it2->second->integrade(0);
			++it2;
		}

	}


	/*
	// --------------------------------------------------------------------------------
	void CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse, std::string name);
	Particule* GetParticule(std::string name);

	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	
	
	ContactRegistry* GetContactRegistry() { return &_contactregistry; }
	*/
private:

	
	std::map<std::string, RigidBody*> _physicobjectsRB;

	/*
	std::map<std::string, Particule*> _physicobjects;
	ContactRegistry _contactregistry;
	ForceRegistry _forceregistry;
	*/
	ForceRegistryRigid _forceregistryRB;


	std::list<std::pair<RigidBody*, RigidBody*>> BroadPhase(std::list<std::pair<RigidBody*, RigidBody*>> listbodies);
	
};

#endif

