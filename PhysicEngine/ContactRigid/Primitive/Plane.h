#pragma once
#include "Primitive.h"

class Plane : public Primitive
{
public:
	Vector3D normal;
	float offset;
};