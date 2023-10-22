
#ifndef FORCEGRAVITY_CLASS_H
#define FORCEGRAVITY_CLASS_H


#include "IForce.h"

class ForceGravity : public IForce
{
private:
	Vector3D gravityStrengh= Vector3D(0, -9.8f, 0);
public:
	virtual std::string getType() { return "Gravity"; }
	virtual OutValues ApplyForce(Particule* object) { return{ false, gravityStrengh * object->getMasse() }; }

};


#endif