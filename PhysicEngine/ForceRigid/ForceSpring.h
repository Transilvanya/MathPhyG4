
#ifndef FORCESPRING_CLASS_H
#define FORCESPRING_CLASS_H


#include "IForceRigid.h"

class ForceSpring : public IForceRigid
{
private:
	RigidBody* otherRigidbody;
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
		Vector3D v = Anchor - otherAnchor;
		Vector3D output = Vector3D(v.getUnitVector()[0], v.getUnitVector()[1], v.getUnitVector()[2]);
		output = output * (-k) * (v.getNorm() - l0);
		bool breakspring = false;

		if (v.getNorm() > MaxLength)
		{
			breakspring = true;
		}

		if (BungeeSpring && v.getNorm() - l0 <= 0)
		{
			return { breakspring, Vector3D(0, 0, 0) };
		}
		else
		{
			//	std::cout << output.getX() << " " << output.getY() << " " << output.getZ() << "\n";

			return { breakspring, output };
		}
	}

};


#endif