#include "Quaternion.h"


Quaternion::Quaternion()
{
	for(int i = 0; i<4; i++)
		value[i] = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	value[0] = w;
	value[1] = x;
	value[2] = y;
	value[3] = z;
}

Quaternion::~Quaternion()
{
}

void Quaternion::Normalized()
{
	float d = sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3]);
	for (int i = 0; i < 4; i++)
	{
		value[i] = value[i] / d;
	}

}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	Quaternion result;
	result.value[0] = this->value[0] * q.value[0] - this->value[1] * q.value[1] - this->value[2] * q.value[2] - this->value[3] * q.value[3];
	result.value[1] = this->value[0] * q.value[1] + this->value[1] * q.value[0] + this->value[2] * q.value[3] - this->value[3] * q.value[2];
	result.value[2] = this->value[0] * q.value[2] - this->value[1] * q.value[3] + this->value[2] * q.value[0] + this->value[3] * q.value[1];
	result.value[3] = this->value[0] * q.value[3] + this->value[1] * q.value[2] - this->value[2] * q.value[1] + this->value[3] * q.value[0];
	return result;
}

void Quaternion::RotateByVector(const Vector3D& q)
{

	Quaternion multiplie;
	Vector3D vecteur = q;
	multiplie.value[0] = 0;
	for (int i = 0; i < 3; i++)
	{
		multiplie.value[i + 1] = vecteur.getVector()[i];
	}
	Quaternion result = *this * multiplie;
	this->value[0] = result.getW();
	this->value[1] = result.getX();
	this->value[2] = result.getY();
	this->value[3] = result.getZ();
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float dt)
{
	Quaternion deltaQ;
	Quaternion q = Quaternion(this->getW(), this->getX(), this->getY(), this->getZ() );
	deltaQ.value[0] = 0;
	for (int i = 0; i < 3; i++)
	{
		deltaQ.value[i + 1] = rotation.getVector()[i] * dt * 0.5;
	}

	this->value[0] += deltaQ.value[0] * q.value[0] - deltaQ.value[1] * q.value[1] - deltaQ.value[2] * q.value[2] - deltaQ.value[3] * q.value[3];
    this->value[1] += deltaQ.value[0] * q.value[1] + deltaQ.value[1] * q.value[0] + deltaQ.value[2] * q.value[3] - deltaQ.value[3] * q.value[2];
    this->value[2] += deltaQ.value[0] * q.value[2] - deltaQ.value[1] * q.value[3] + deltaQ.value[2] * q.value[0] + deltaQ.value[3] * q.value[1];
    this->value[3] += deltaQ.value[0] * q.value[3] + deltaQ.value[1] * q.value[2] - deltaQ.value[2] * q.value[1] + deltaQ.value[3] * q.value[0];

	//this->Normalized();

}