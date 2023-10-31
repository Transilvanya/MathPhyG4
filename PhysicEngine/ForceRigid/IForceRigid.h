
#ifndef IFORCERIGID_CLASS_H
#define IFORCERIGID_CLASS_H


#include "../vector/Vector3D.h"
#include "../RigidBody/RigidBody.h"
#include <string>
#include <iostream>
class IForceRigid
{
private:
	bool ForceApplied = true;

	Vector3D force = Vector3D(0, 0, 0);
public:



	bool IsForceApplied();
	void SetForceApplied(bool value);
	virtual std::string getType();
	//the return define wheater the force should be removed after this tick
	virtual bool ApplyForce(RigidBody* object);

};


#endif