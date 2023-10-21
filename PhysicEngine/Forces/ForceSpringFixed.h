
#ifndef FORCESPRINGFIXED_CLASS_H
#define FORCESPRINGFIXED_CLASS_H


#include "IForce.h"

class ForceSpringFixed : public IForce
{
private:
	Vector3D anchorpoint;

	bool BungeeSpring = false; // only create a force when v.norm > l0

	float MaxLength;
	float k;
	float l0;
	
public:
	ForceSpringFixed(Vector3D _anchor, float _k, float _l0, float _MaxLength, bool _BungeeSpring) { k = _k; l0 = _l0; anchorpoint = _anchor; BungeeSpring = _BungeeSpring; MaxLength = _MaxLength; }
	virtual std::string getType() { return "ForceSpringFixed"; }
	virtual OutValues ApplyForce(Particule* object)
	{ 
		Vector3D v = object->getPostion() - anchorpoint;
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
				//std::cout << output.getX() << " " << output.getY() << " " << output.getZ() << "\n";

			return  { breakspring, output };
		}
		
	}

};


#endif