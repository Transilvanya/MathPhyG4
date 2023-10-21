#include "ParticleRod.h"

unsigned int ParticleRod::addContact(ParticleContact* contact, int limit) const
{
	// Find the length of the rod
	float currentLen = currentLength();

	// Check if we're overextended
	if (currentLen == maxLength)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particule[0] = particule[0];
	contact->particule[1] = particule[1];

	// Calculate the normal
	Vector3D normal = particule[1]->getPosition() - particule[0]->getPosition();
	normal.getNorm();

	// The contact normal depends on whether we're extending or compressing
	if (currentLen > limit)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLen - limit;
	}
	else
	{
		contact->contactNormal = normal * -1;
		contact->penetration = maxLength - currentLen;
	}

	// Always use zero restitution (no bounciness)
	contact->restitution = 0;

	return 1;
}	