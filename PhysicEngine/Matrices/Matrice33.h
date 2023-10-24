#pragma once
#ifndef MATHPHYG4_MATRICE33_H
#define MATHPHYG4_MATRICE33_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"

class Matrice33
{
public:
	Matrice33();
	~Matrice33();


	//combinaison de transformation lineaire
	Matrice33 operator*(const Matrice33& m) const;

	// Transform of a vector
	Vector3D operator*(const Vector3D& v) const;

	//renvoie l'inverse de la matrice
	Matrice33 Inverse();

	//renvoie le transpose de la matrice
	Matrice33 Transpose();

	// set une matrice base sur un quaternion
	void setOrientation(const Quaternion& q);

private:

	float value[9];

};


#endif // !MATHPHYG4_MATRICE33_H