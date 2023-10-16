#pragma once
#ifndef MATHPHYG4_PARTICLECONTACT_H
#define MATHPHYG4_PARTICLECONTACT_H
#include "../Particules/Particules.h"

class ParticleContact 
{
public:
	ParticleContact();
	~ParticleContact();

	Particules* particule[2];

	float restitution;

	float penetration;
	
	Vector3D contactNormal;

	void resolve(float duration);

	float calculateSeparatingVelocity() const;


private:
	void resolveVelocity();

	void resolveInterpenetration();
};

#endif // MATHPHYG4_PARTICLECONTACT_H
