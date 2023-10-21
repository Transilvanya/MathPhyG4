#pragma once
#ifndef MATHPHYG4_PARTICLECONTACTRESOLVER_H
#define MATHPHYG4_PARTICLECONTACTRESOLVER_H
#include "ParticleContact.h"


class ParticleContactResolver 
{
protected:
	unsigned int iterations;

public:
	void resolveContacts (ParticleContact* contactArray, unsigned int numContacts, float duration);
};

#endif // MATHPHYG4_PARTICLECONTACTRESOLVER_H