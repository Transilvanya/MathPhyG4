#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3D relativePos = particule[0]->getPosition() - particule[1]->getPosition();
	return relativePos.distance();
}
