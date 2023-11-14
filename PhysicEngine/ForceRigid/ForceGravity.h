#ifndef FORCEGRAVITY_CLASS_H
#define FORCEGRAVITY_CLASS_H


#include "IForceRigid.h"

class ForceGravity : public IForceRigid
{
private:
	Vector3D gravityStrengh = Vector3D(0, -9.8f, 0);
public:
	virtual std::string getType() { return "Gravity"; }
	virtual OutValues ApplyForce(RigidBody* object) { return{ false, gravityStrengh * object->getMasse() }; }

};


#endif