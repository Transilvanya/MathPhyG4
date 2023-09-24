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
	Vector3D getForce();
	Vector3D getPostion();
	Vector3D getVitesse();
	Vector3D getAcceleration();

	//setter
	void setMasse(float newMasse);
	void setInverseMasse(float newMasse);
	void setVectorAcceleration(Vector3D newAcceleration);
	void setForce(Vector3D newforce);

	//method
	void intergrade(float DT);




private:
	Vector3D vectorPosition;
	Vector3D vectorVitesse;
	Vector3D vectorAcceleration;
	Vector3D force;

	float inverseMasse = 1.0f;
	float damping = 0.99f;
};

#endif //MATHPHYG4_PARTICULES_H