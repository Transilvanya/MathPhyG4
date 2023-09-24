#include "Particules.h"


Particules::Particules()
{
}

Particules::Particules(Vector3D position, Vector3D vitesse, Vector3D acceleration)
{
	vectorPosition = position;
	vectorVitesse = vitesse;
	vectorAcceleration = acceleration;

	force = Vector3D(0.0f,0.0f,0.0f);
}

Particules::~Particules()
{
}

float Particules::getMasse()
{
	return 1 / this->inverseMasse;
	return 0;
}

float Particules::getInverseMasse()
{
	return this->inverseMasse;
	return 0;
}

Vector3D Particules::getForce()
{
	return force;
}

Vector3D Particules::getPostion()
{
	return vectorPosition;
}

Vector3D Particules::getVitesse()
{
	return vectorVitesse;
}

Vector3D Particules::getAcceleration()
{
	return vectorAcceleration;
}

void Particules::setMasse(float newMasse)
{
	this->inverseMasse = 1 / newMasse;
}

void Particules::setInverseMasse(float newMasse)
{
	this->inverseMasse = newMasse;
}

void Particules::setVectorAcceleration(Vector3D newAcceleration)
{
	this->vectorAcceleration = newAcceleration;
}

void Particules::setForce(Vector3D newforce)
{
	force = newforce;
}

void Particules::intergrade(float DT){
	this->vectorPosition = this->vectorPosition + (this->vectorVitesse * DT);
	this->vectorAcceleration = force * this->getInverseMasse();
	this->vectorVitesse = this->vectorVitesse * damping + (this->vectorAcceleration * DT);
}

