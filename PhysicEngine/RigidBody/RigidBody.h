#pragma once
#ifndef MATHPHYG4_RIGIDBODY_H
#define MATHPHYG4_RIGIDBODY_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"
#include "../Matrices/Matrice34.h"
#include "../Matrices/Matrice33.h"

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	//Intergrade the rigid body by modifying the position, orientation and velocity
	void Intergrate(float dt);

private:
	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D vitesse;

	Quaternion orientation;

	Vector3D rotation;

	Matrice34 transformMatrix;

	//appel a chaque frame
	//calcule le transformeMatrice
	//and normalize the orientation
	void CalculateDerivedData();
};
#endif // !MATHPHYG4_RIGIDBODY_H