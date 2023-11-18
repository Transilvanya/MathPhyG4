
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include "Particules/Particule.h"
#include <iostream>
#include "Forces/ForceRegistry.h"
#include "Contact/ContactRegistry.h"
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

	void CreateRigidCuboid(float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);
	Particule* GetRigidCuboid(std::string name);

	void CreateRigidCylinder(float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);
	Particule* GetRigidCylinder(std::string name);




	// --------------------------------------------------------------------------------
	void CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse, std::string name);
	Particule* GetParticule(std::string name);

	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	
	ContactRegistry* GetContactRegistry() { return &_contactregistry; }
private:

	std::map<std::string, Particule*> _physicobjects;
	std::map<std::string, RigidBody*> _physicobjectsRB;

	ContactRegistry _contactregistry;
	ForceRegistry _forceregistry;
	//ForceRegistryRigid _forceregistryRB;
};

#endif

