#pragma once
#ifndef MATHPHYG4_PARTICLELINK_H
#define MATHPHYG4_PARTICLELINK_H
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
public:
	Particules* particule[2];

	float currentLength() const;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

#endif // MATHPHYG4_PARTICLELINK_H
