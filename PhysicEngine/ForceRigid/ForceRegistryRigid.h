
#ifndef FORCEREGISTRYRIGID_CLASS_H
#define FORCEREGISTRYRIGID_CLASS_H


#include <map>
#include <list>
#include <iostream>
#include "../RigidBody/RigidBody.h"
#include "IForceRigid.h"
#include "ForceGravity.h"
#include "SimpleForce.h"
#include "ForceDrag.h"
#include "ForceBuoyancy.h"
#include "ForceSpring.h"
#include "ForceSpringFixed.h"


class ForceRegistryRigid
{
private:

	struct ForceApplication
	{
		IForceRigid* force;
		Vector3D ApplicationPoint; //ignore if global force
		bool IsGlobalForce;
		bool isGlobalCoordinate; //if it is not a global point define if the point is local or global
	};

	struct RigidBodyEntry
	{
		RigidBody* rigidbody;
		std::map<std::string, ForceApplication> forces;
	};

	std::map<std::string, RigidBodyEntry> ForceEntries;

public:
	// clear ForceEntries and forces and destroy the pointer of the forces
	~ForceRegistryRigid();


	/* for every entry, call AddForce,AddForcePoint or AddForceAtBodyPoint from rigidbody */
	void ApplyForces();

	//create and remove an entry; the first parameter of the map is the name of the object
	void AddRigidBody(RigidBody* object);
	void RemoveRigidBody(std::string name);

	//create a ForceApplication with the corresponding parameter; the first parameter of the map in forces is name
	void AddForceToRigidBodyAtPoint(RigidBody* object, IForceRigid* force, Vector3D ApplicationPoint, std::string name, bool _isGlobalCoordinate);
	void AddForceToRigidBody(RigidBody* object, IForceRigid* force, std::string name);
	//remove force named nameForce in entry named nameObject
	void RemoveForceFromRigidBody(std::string nameObject, std::string nameForce);


	IForceRigid* GetForce(std::string nameObject, std::string nameForce);

	//get the list of the name of all the force in the entry named name
	std::list<std::string> GetForcesOfRigidBody(std::string name);



	void AddForceGravityToRigidBody(RigidBody* rigidbody, std::string forcename);

	void AddForceSimpleToRigidBody(Vector3D forcevector, RigidBody* rigidbody, std::string forcename);
	void AddForceSimpleToRigidBodyAtPoint(Vector3D forcevector, RigidBody* rigidbody, std::string forcename, Vector3D ApplicationPoint, bool _isGlobalCoordinate);

	void AddForceDragToRigidBody(float k1, float k2, RigidBody* rigidbody, std::string forcename);

	void AddForceBuoyancyToRigidBody(float liquidheight, float liquiddensity, RigidBody* rigidbody, std::string forcename);


	void AddForceSpringFixedToRigidBody(Vector3D anchor, float k, float l0, float maxlength, bool bungeespring, RigidBody* rigidbody, Vector3D _Anchor, std::string forcename);

	//create two force, one on each rigidboy
	void AddForceSpringToRigidBody(float k, float l0, float maxlength, bool bungeespring, RigidBody* rigidbody1, RigidBody* rigidbody2, Vector3D _Anchor1, Vector3D _Anchor2, std::string forcename);


};


#endif