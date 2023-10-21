#include "ParticleCable.h"

unsigned int ParticleCable::addContact(ParticleContact* contact, int limit) const
{
	// Find the length of the cable
	float length = currentLength();

	// Check if we're over-extended
	if (length < maxLength)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particule[0] = particule[0];
	contact->particule[1] = particule[1];

	// Calculate the normal
	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.getNorm();
	contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}