#pragma once
#ifndef MATHPHYG4_PARTICLECONTACTGENERATOR_H
#define MATHPHYG4_PARTICLECONTACTGENERATOR_H
#include "ParticleContact.h"


class ParticleContactGenerator {

public:
		ParticleContactGenerator();
		~ParticleContactGenerator();
		virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

#endif // MATHPHYG4_PARTICLECONTACTGENERATOR_H