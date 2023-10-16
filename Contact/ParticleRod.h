#pragma once
#ifndef MATHPHYG4_PARTICLEROD_H
#define MATHPHYG4_PARTICLEROD_H
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
		float length;

		unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

#endif // MATHPHYG4_PARTICLEROD_H
