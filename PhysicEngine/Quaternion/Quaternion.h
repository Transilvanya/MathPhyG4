#pragma once

#ifndef MATHPHYG4_QUATERNION_H
#define MATHPHYG4_QUATERNION_H
#define _USE_MATH_DEFINES
#include "../vector/Vector3D.h"
#include <math.h>
//#include "../Matrices/Matrice34.h"

class Quaternion
{
public:
	
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	~Quaternion();

	//normalise en multipliant le quaternion par l'inverse de sa magnitude
	void Normalized();

	//Matrice34 getMatrice34();
	//Matrice33 getMatrice33();

	Quaternion operator*(const Quaternion& q);

	//rotate le quaternion par un vecteur
	//multiplie le par q = (0, dx, dy, dx)
	void RotateByVector(const Vector3D& q);

	//apply quaternion update by angular velocity
	void UpdateByAngularVelocity(const Vector3D& rotation, float dt);

	float getW() const { return value[0]; }
	float getX() const { return value[1]; }
	float getY() const { return value[2]; }
	float getZ() const { return value[3]; }

private:
	float value[4];

	//w + xi + yj + zk
	//w scalaire i j k nombre imaginaire
};

#endif // !MATHPHYG4_QUATERNION_H
