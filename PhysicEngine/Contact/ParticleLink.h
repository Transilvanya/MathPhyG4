
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
};

#endif // MATHPHYG4_PARTICLELINK_H
