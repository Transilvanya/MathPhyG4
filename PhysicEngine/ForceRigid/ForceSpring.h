
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
	virtual OutValues ApplyForce(RigidBody* object)
	{
		OutValues out;
		out.force = Vector3D(0, 0, 0);
		out.torque = Vector3D(0, 0, 0);

		Vector3D p1 = object->getTransform().getGlobalPosition() + object->getTransform().getLocalToGlobal().transform(Anchor);
		Vector3D p2 = otherParticule->getTransform().getGlobalPosition() + otherParticule->getTransform().getLocalToGlobal().transform(otherAnchor);

		Vector3D v = p2 - p1;
		float l = v.norm();

		if (l > MaxLength)
		{
			v = v * (1 / l);
			out.force = v * (l - MaxLength) * k;
		}
		else if (BungeeSpring && l > l0)
		{
			v = v * (1 / l);
			out.force = v * (l - l0) * k;
		}

		return out;
	}
};


#endif