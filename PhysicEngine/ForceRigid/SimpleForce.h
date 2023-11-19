
#ifndef SIMPLEFORCE_CLASS_H
#define SIMPLEFORCE_CLASS_H


#include <string>
#include <iostream>
#include "IForceRigid.h"
#include "../vector/Vector3D.h"

class SimpleForce : public IForceRigid
{
private:
	Vector3D force = Vector3D(0, 0, 0);
public:

	//static linear force
	SimpleForce(Vector3D vector)
	{
		force = vector;
	}

	virtual std::string getType() { return "Force"; }
	OutValues ApplyForce(RigidBody* object) { return { false, force }; }

};


#endif