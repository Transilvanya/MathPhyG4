
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include "Particules/Particule.h"
#include <iostream>
#include "Forces/ForceRegistry.h"
#include "Contact/ContactRegistry.h"

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

	void CreateRigidBody(Matrice33 _InverseTenseur, std::string _Type, float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);

	//call CreateRigidBody with the correct Tenseur and type
	void CreateRigidSphere(float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);

	void CreateRigidCuboid(float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);

	void CreateRigidCylinder(float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);





	// --------------------------------------------------------------------------------
	void CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse, std::string name);
	Particule* GetParticule(std::string name);



	// --------------------------------------------------------------------------------
	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	
	ContactRegistry* GetContactRegistry() { return &_contactregistry; }
private:

	std::map<std::string, Particule*> _physicobjects;

	ContactRegistry _contactregistry;
	ForceRegistry _forceregistry;
};

#endif

