
#ifndef FORCEBUOYANCY_CLASS_H
#define FORCEBUOYANCY_CLASS_H


#include "IForceRigid.h"

class ForceBuoyancy : public IForceRigid
{
private:
	float LiquidHeight;
	float LiquidDensity;


public:

	ForceBuoyancy(float _LiquidHeight, float _LiquidDensity)
	{
		LiquidHeight = _LiquidHeight;
		LiquidDensity = _LiquidDensity;
	}

	virtual std::string getType() { return "ForceBuoyancy"; }
	virtual OutValues ApplyForce(RigidBody* object)
	{
		float MaxDepth = 0.0f;
		float ObjectVolume = 0.0f;

		MaxDepth = 1;
		ObjectVolume = object->GetVolume();



		float d = (object->getPosition().getY() - LiquidHeight - MaxDepth) / (2 * MaxDepth);


		Vector3D output = Vector3D(0, 0, 0);



		if (d >= 0)
		{
			output.setY(0);
		}
		else
		{
			if (d <= -1)
			{
				output.setY(ObjectVolume * LiquidDensity);
			}
			else
			{
				output.setY(-d * ObjectVolume * LiquidDensity);
			}
		}

		//std::cout << MaxDepth << " " << ObjectVolume << " " << object->getPosition().getY() << " "<< output.getY() << " "<< d << "\n";

		return { false, output };
	}

};


#endif