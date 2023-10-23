#pragma once
#ifndef MATHPHYG4_PARTICULE_H
#define MATHPHYG4_PARTICULE_H

#include "../Vector/Vector3D.h"
#include <iostream>
class Particule {


public: 
	//constructor
	Particule(Vector3D position, Vector3D vitesse, Vector3D acceleration, float masse, std::string name);

	
	//destructor
	~Particule();
	
	//getter
	virtual float getMasse();
	virtual float getInverseMasse();
	virtual Vector3D getForce();
	virtual Vector3D getPosition();
	virtual Vector3D getVitesse();
	virtual Vector3D getAcceleration();
	virtual bool isVibrating() { return vibrating; }

	//setter
	virtual void setPosition(Vector3D newPosition);
	virtual void setVitesse(Vector3D newVitesse);
	virtual void setAcceleration(Vector3D newAcceleration);
	virtual void setMasse(float newMasse);
	virtual void setInverseMasse(float newMasse);
	virtual void setVectorAcceleration(Vector3D newAcceleration);
	virtual void setForce(Vector3D newforce);
	virtual void activateVibration() { vibrating = true; }
	virtual void desactivateVibration() { vibrating = false; };

	//method
	virtual void integrade(float DT);

	virtual Vector3D getDeltaPosition();
	virtual Vector3D getPrevPosition();

	std::string GetName();

private:
	std::string particulename;

	Vector3D vectorPrevPosition;
	Vector3D vectorPosition;
	Vector3D vectorVitesse;
	Vector3D vectorAcceleration;

	Vector3D force;

	float inverseMasse = 1.0f;
	bool vibrating = true;
};

#endif //MATHPHYG4_PARTICULES_H