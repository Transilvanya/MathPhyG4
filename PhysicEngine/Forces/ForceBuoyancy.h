
#ifndef FORCEBUOYANCY_CLASS_H
#define FORCEBUOYANCY_CLASS_H


#include "IForce.h"

class ForceBuoyancy : public IForce
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
	virtual OutValues ApplyForce(Particule* object)
	{
		float MaxDepth = 0.0f;
		float ObjectVolume = 0.0f;

		//if (object->getType() == 0)//particule
		//{
			MaxDepth = 1;
			ObjectVolume = (4.0f / 3) * 3.14;
		//}
			/*
		if (object->getType() == 1)//sphere
		{
			float objectradius = ((SphereObject*)object)->GetRadius();
			MaxDepth = objectradius;
			ObjectVolume = 4.0f/3 * 3.14 * objectradius * objectradius * objectradius;
		}
		*/
		

		float d = (object->getPostion().getY() - LiquidHeight - MaxDepth) / (2 * MaxDepth);


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

		//std::cout << MaxDepth << " " << ObjectVolume << " " << object->getPostion().getY() << " "<< output.getY() << " "<< d << "\n";

		return { false, output };
	}

};


#endif