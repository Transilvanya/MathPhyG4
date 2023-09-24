#include "Particules.h"


Particules::Particules()
{
}

Particules::Particules(Vector3D position, Vector3D vitesse, Vector3D acceleration)
{
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

void Particules::intergrade() {
	int DT = 5;
	this->vectorPosition = this->vectorPosition + (this->vectorVitesse * DT);
	this->vectorAcceleration = force * this->getInverseMasse();
	this->vectorVitesse = this->vectorVitesse * damping + (this->vectorAcceleration * DT);
}

