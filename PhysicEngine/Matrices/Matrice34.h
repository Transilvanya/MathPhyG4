#pragma once
#ifndef MATHPHYG4_MATRICE34_H
#define MATHPHYG4_MATRICE34_H

#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"
#include "Matrice33.h"

class Matrice34
{
public:
	//combinaison d'une transformation affine
	Matrice34 operator*(const Matrice34& m) const;

	//transformation d'un vecteur
	Vector3D operator*(const Vector3D& v) const;

	//prend la matrice inverse
	Matrice34 Inverse();

	// met la matrice de base sur un quaternion et une position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3D& pos);

	//transforme la position
	Vector3D TransformPosition(const Vector3D& v);

	//transforme la direction en ingnorant la translation
	Vector3D TransformDirection(const Vector3D& v);
private:
	float values [12];
};

#endif // !MATHPHYG4_MATRICE34_H