#include "Matrice33.h"


//combinaison de transformation lineaire
Matrice33 Matrice33::operator*(const Matrice33& m) const
{
	Matrice33 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) 
		{
			for (int k = 0; k < 3; k++) {
				result.value[3 * i + j] = this->value[3*i + k] * this->value[3*k +j];
			}
		}
	}
	return result;
}

Vector3D Matrice33::operator*(const Vector3D& v) const
{
	Vector3D result = Vector3D(0,0,0);
	for (int i = 0; i < 3; i++) {
		result.setX(result.getX() + this->value[i] * v.getVector()[i]);
		result.setY(result.getY() + this->value[i+3] * v.getVector()[i]);
		result.setZ(result.getZ() + this->value[i+6] * v.getVector()[i]);
	}
	return result;
}

Matrice33 Matrice33::operator*(const float& f) const
{
	Matrice33 result;
	for (int i = 0; i < 9; i++) {
		result.value[i] = this->value[i] * f;
	}
	return result;
}

Matrice33 Matrice33::Inverse()
{
	Matrice33 result;
	Matrice33 adjointe = this->getAdjointe();
	float determinant = this->getDeterminant();
	if (determinant != 0) {
		result =  adjointe * (1 / determinant);
	}
	return result;
}

Matrice33 Matrice33::Transpose()
{
	Matrice33 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			result.value[i*3+j] = this->value[j*3+i];
		}
	}
	return result;
}


void Matrice33::setOrientation(const Quaternion& q)
{
	float wx, wy, wz, xx, xy, xz, yy, yz, zz;
	wx = q.getW() * q.getX();
	wy = q.getW() * q.getY();
	wz = q.getW() * q.getZ();
	xx = q.getX() * q.getX();
	xy = q.getX() * q.getY();
	xz = q.getX() * q.getZ();
	yy = q.getY() * q.getY();
	yz = q.getY() * q.getZ();
	zz = q.getZ() * q.getZ();
	

	this->value[0] = 1 - 2 * (yy + zz);
	this->value[1] = 2 * (xy - wz);
	this->value[2] = 2 * (xz + wy);
	this->value[3] = 2 * (xy + wz);
	this->value[4] = 1 - 2 * (xx + zz);
	this->value[5] = 2 * (yz - wx);
	this->value[6] = 2 * (xz - wy);
	this->value[7] = 2 * (yz + wx);
	this->value[8] = 1 - 2 * (xx + yy);


}

float Matrice33::getDeterminant()
{
	int result = 0;
	result = this->value[0] * (this->value[4] * this->value[8] - this->value[5] * this->value[7]) - this->value[1] * (this->value[3] * this->value[8] - this->value[5] * this->value[6]) + this->value[2] * (this->value[3] * this->value[7] - this->value[4] * this->value[6]);
	return result;
}

Matrice33 Matrice33::getAdjointe() const 
{
	Matrice33 adjointe;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			adjointe.value[i * 3 + j] = this->value[(i + 1) % 3 * 3 + (j + 1) % 3] * this->value[(i + 2) % 3 * 3 + (j + 2) % 3] - this->value[(i + 1) % 3 * 3 + (j + 2) % 3] * this->value[(i + 2) % 3 * 3 + (j + 1) % 3];
		}
	}

	return adjointe;
}
