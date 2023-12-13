#pragma once
#include "Primitive.h"

class Box : public Primitive
{
public:
	RigidCuboid* body;
	Vector3D halfSize;

	float transformToAxis(const Box& box, Vector3D& axis)
	{
		return
			box.halfSize.getX() * abs(axis & box.body->getAxis(0)) +
			box.halfSize.getY() * abs(axis & box.body->getAxis(1)) +
			box.halfSize.getZ() * abs(axis & box.body->getAxis(2));
	}

	bool overlapOnAxis(const Box& firstBox, const Box& secondBox, Vector3D& axis)
	{
		float firstProjection = transformToAxis(firstBox, axis);
		float secondProjection = transformToAxis(secondBox, axis);

		Vector3D toCentre = secondBox.body->getAxis(2) - firstBox.body->getAxis(2);

		float distance = abs(toCentre & axis);

		return (distance < firstProjection + secondProjection);
	}
};