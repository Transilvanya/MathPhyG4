#pragma once
#ifndef MATHPHYG4_PARTICULES_H
#define MATHPHYG4_PARTICULES_H

#include "../Vector/Vector3D.h"

class Particules {

public: 
	//constructor
	Particules();
	Particules(Vector3D position, Vector3D vitesse, Vector3D acceleration);

	
	//destructor
	~Particules();
	
	//getter
	float getMasse();
	float getInverseMasse();

	//setter
	void setMasse(float newMasse);
	void setInverseMasse(float newMasse);
	void setVectorAcceleration(Vector3D newAcceleration);


	//method
	void intergrade();



private:
	Vector3D vectorPosition;
	Vector3D vectorVitesse;
	Vector3D vectorAcceleration;
	Vector3D force;

	float inverseMasse;
	float damping;
};

#endif //MATHPHYG4_PARTICULES_H