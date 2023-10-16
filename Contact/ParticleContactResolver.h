#pragma once
#ifndef MATHPHYG4_PARTICLECONTACTRESOLVER_H
#define MATHPHYG4_PARTICLECONTACTRESOLVER_H
#include "../Particules/Particules.h"
#include "ParticleContact.h"


class ParticleContactResolver 
{
protected:
	unsigned int iterations;

public:
	ParticleContactResolver(unsigned int iterations);
	~ParticleContactResolver();
	void resolveContacts (ParticleContact* contactArray, unsigned int numContacts, float duration);
};

#endif // MATHPHYG4_PARTICLECONTACTRESOLVER_H