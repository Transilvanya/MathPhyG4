#pragma once
#ifndef MATHPHYG4_PARTICLEROD_H
#define MATHPHYG4_PARTICLEROD_H
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
		float maxLength;

		unsigned int addContact(ParticleContact* contact, int limit) const;
};

#endif // MATHPHYG4_PARTICLEROD_H
