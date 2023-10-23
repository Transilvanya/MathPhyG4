
#ifndef SIMPLEFORCE_CLASS_H
#define SIMPLEFORCE_CLASS_H


#include <string>
#include <iostream>
#include "IForce.h"
#include "../vector/Vector3D.h"
#include "../Particules/Particule.h"

class SimpleForce : public IForce
{
private:
	Vector3D force = Vector3D(0, 0, 0);
public:

	SimpleForce(Vector3D vector)
	{
		force = vector;
	}

	virtual std::string getType() { return "Force"; }
	OutValues ApplyForce(Particule* object) { return { false, force }; }

};


#endif