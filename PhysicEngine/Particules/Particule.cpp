#include "Particule.h"


std::string Particule::GetName()
{
	return particulename;
}

Particule::Particule(Vector3D position, Vector3D vitesse, Vector3D acceleration, float masse, std::string name)
{
	particulename = name;
	inverseMasse = 1 / masse;
	vectorPosition = position;
	vectorVitesse = vitesse;
	vectorAcceleration = acceleration;

	force = Vector3D(0.0f,0.0f,0.0f);
}

Particule::~Particule()
{
}

float Particule::getMasse()
{
	return 1 / this->inverseMasse;
	return 0;
}

float Particule::getInverseMasse()
{
	return this->inverseMasse;
	return 0;
}

Vector3D Particule::getForce()
{
	return force;
}

Vector3D Particule::getPosition()
{
	return vectorPosition;
}

Vector3D Particule::getVitesse()
{
	return vectorVitesse;
}

Vector3D Particule::getAcceleration()
{
	return vectorAcceleration;
}

void Particule::setPosition(Vector3D newPosition)
{
	vectorPosition = newPosition;
}

void Particule::setVitesse(Vector3D newVitesse)
{
	vectorVitesse = newVitesse;
}

void Particule::setAcceleration(Vector3D newAcceleration)
{
	vectorAcceleration = newAcceleration;
}

void Particule::setMasse(float newMasse)
{
	inverseMasse = 1 / newMasse;
}

void Particule::setInverseMasse(float newMasse)
{
	inverseMasse = newMasse;
}

void Particule::setVectorAcceleration(Vector3D newAcceleration)
{
	vectorAcceleration = newAcceleration;
}

void Particule::setForce(Vector3D newforce)
{
	force = newforce;
}

void Particule::integrade(float DT){
	vectorPosition = vectorPosition + (vectorVitesse * DT);
	vectorAcceleration = force * getInverseMasse();
	vectorVitesse = vectorVitesse + (vectorAcceleration * DT);

	//std::cout << particulename << " " << vectorPosition.getX() << " " << vectorPosition.getY() << " " << vectorPosition.getZ() << "\n";
	//std::cout << "\t" << force.getX() << " " << force.getY() << " " << force.getZ() << "\n";
}

Vector3D Particule::getDeltaPosition() { return vectorPosition - vectorPrevPosition; }
Vector3D Particule::getPrevPosition() { return vectorPrevPosition; }