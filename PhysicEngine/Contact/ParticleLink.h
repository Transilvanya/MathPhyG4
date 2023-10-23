
#ifndef PARTICLELINK_CLASS_H
#define PARTICLELINK_CLASS_H

#include "../Particules/Particule.h"
#include "ParticleContact.h"

class ParticleLink
{
public:
	Particule* particule[2];

	ParticleLink(Particule* p0, Particule* p1)
	{
		particule[0] = p0;
		particule[1] = p1;
	}

	virtual void ApplyLink() 
	{ 
	
	}

	//length of link
	//float currentLength() const;


	//virtual unsigned int addContact(ParticleContact* contact, int limit) const = 0;
};

#endif // MATHPHYG4_PARTICLELINK_H
