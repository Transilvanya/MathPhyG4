#pragma once
#ifndef MATHPHYG4_PARTICLECABLE_H
#define MATHPHYG4_PARTICLECABLE_H
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	float maxLength;
	float restitution;

	unsigned int addContact(ParticleContact* contact, int limit) const;
};

#endif // MATHPHYG4_PARTICLECABLE_H