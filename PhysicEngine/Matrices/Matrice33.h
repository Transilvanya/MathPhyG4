#pragma once
#ifndef MATHPHYG4_MATRICE33_H
#define MATHPHYG4_MATRICE33_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"

class Matrice33
{
public:

	//combinaison de transformation lineaire
	Matrice33 operator*(const Matrice33& m) const;

	// Transform of a vector
	Vector3D operator*(const Vector3D& v) const;

	Matrice33 operator*(const float& f) const;

	//renvoie l'inverse de la matrice
	Matrice33 Inverse();

	//renvoie le transpose de la matrice
	Matrice33 Transpose();

	// set the matrix base on a quaternion
	void setOrientation(const Quaternion& q);

	float& getValues(int i) { return value[i]; }



private:

	float value[9];
	float getDeterminant();
	Matrice33 getAdjointe() const;
};


#endif // !MATHPHYG4_MATRICE33_H