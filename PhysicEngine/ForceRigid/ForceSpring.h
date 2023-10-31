
#ifndef FORCESPRING_CLASS_H
#define FORCESPRING_CLASS_H


#include "IForceRigid.h"

class ForceSpring : public IForceRigid
{
private:
	RigidBody* otherParticule;
	Vector3D otherAnchor;

	//anchore of the spring in local coordinate
	Vector3D Anchor;

	bool BungeeSpring = false; // only create a force when v.norm > l0

	float MaxLength;
	float k;
	float l0;

public:
	ForceSpring(RigidBody* _otherbody, Vector3D _otherAnchor,Vector3D _Anchor, float _k, float _l0, float _MaxLength, bool _BungeeSpring);
	virtual std::string getType() { return "ForceSpring"; }
	virtual bool ApplyForce(RigidBody* object);
};


#endif