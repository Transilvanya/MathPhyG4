
#ifndef FORCESPRINGFIXED_CLASS_H
#define FORCESPRINGFIXED_CLASS_H


#include "IForceRigid.h"

class ForceSpringFixed : public IForceRigid
{
private:
	Vector3D anchorpoint;

	Vector3D RigidBodyAnchor;

	bool BungeeSpring = false; // only create a force when v.norm > l0

	float MaxLength; // breaking length of the spring
	float k;
	float l0;
	
public:
	ForceSpringFixed(Vector3D _anchor, Vector3D _rigidbodyanchor, float _k, float _l0, float _MaxLength, bool _BungeeSpring) { k = _k; l0 = _l0; RigidBodyAnchor = _rigidbodyanchor ; anchorpoint = _anchor; BungeeSpring = _BungeeSpring; MaxLength = _MaxLength; }
	virtual std::string getType() { return "ForceSpringFixed"; }
	virtual OutValues ApplyForce(RigidBody* object)
	{
		

		Vector3D v = object->GettransformMatrix() * RigidBodyAnchor - anchorpoint;

		Vector3D output = Vector3D(v.getUnitVector()[0], v.getUnitVector()[1], v.getUnitVector()[2]);
		output = output * (-k) * (v.getNorm() - l0);

		bool breakspring = false;

		/*
		std::cout << "RB anchor " << RigidBodyAnchor.getX() << "\t" << RigidBodyAnchor.getY() << "\t" << RigidBodyAnchor.getZ() << "\n";
		std::cout << "RB anchor global " << (object->GettransformMatrix() * RigidBodyAnchor).getX() << "\t" << (object->GettransformMatrix() * RigidBodyAnchor).getY() << "\t" << (object->GettransformMatrix() * RigidBodyAnchor).getZ() << "\n";
		std::cout << "anchor " << anchorpoint.getX() << "\t" << anchorpoint.getY() << "\t" << anchorpoint.getZ() << "\n";
		std::cout << "V " << v.getX() << "\t" << v.getY() << "\t" << v.getZ() << "\n";
		std::cout << "output " << output.getX() << " " << output.getY() << " " << output.getZ() << "\n\n";
		std::cout << "output local -> global " << (object->GettransformMatrix() * output).getX() << " " << (object->GettransformMatrix() * output).getY() << " " << (object->GettransformMatrix() * output).getZ() << "\n\n";
		std::cout << "output global -> local " << (object->GettransformMatrix().Inverse() * output).getX() << " " << (object->GettransformMatrix().Inverse() * output).getY() << " " << (object->GettransformMatrix().Inverse() * output).getZ() << "\n\n";
		*/

		output = object->GettransformMatrix().Inverse() * output;
		

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

			return  { breakspring, output };
		}
	}
};


#endif