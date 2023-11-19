
#ifndef FORCEDRAG_CLASS_H
#define FORCEDRAG_CLASS_H


#include "IForceRigid.h"

class ForceDrag : public IForceRigid
{
private:
	float k1;
	float k2;
public:
	ForceDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	virtual std::string getType() { return "ForceDrag"; }
	virtual OutValues ApplyForce(RigidBody* object)
	{
		Vector3D v = object->getVitesse();

		if (v.getNorm() != 0)
		{
			Vector3D output = Vector3D(v.getUnitVector()[0], v.getUnitVector()[1], v.getUnitVector()[2]);

			output = output * (-1) * (k1 * v.getNorm() + k2 * v.getNorm() * v.getNorm());

			//std::cout << output.getX() << " " << output.getY() << " " << output.getZ() << "\n";
			return { false, output };
		}
		else
		{
			return { false, Vector3D(0, 0, 0) };
		}

	}

};


#endif