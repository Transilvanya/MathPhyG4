#pragma once
#include "../../RigidBody/RigidBody.h"
#include "../../Matrices/Matrice34.h"


class Primitive 
{
public:
	RigidBody* body;
	//represente la rotation et la translation de la primitive par rapport au corps
	Matrice34 offset;
	enum PrimitiveType
	{
		BOX,
		SPHERE,
		PLANE
	};
	PrimitiveType type;

};
