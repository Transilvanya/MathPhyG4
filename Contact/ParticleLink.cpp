#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3D relativePos = particule[0]->getPosition() - particule[1]->getPosition();
	return relativePos.distance();
}

//take a pointer to an array of contact and the numver of contact left to be generated
int ParticleLink::addContact(ParticleContact* contact, int limit) const
{
	// Find the length of the rod
	float currentLen = currentLength();

	// Check if we're overextended
	if (currentLen == length)
	{
		return 0;
	}

	// Otherwise return the contact
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	// Calculate the normal
	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalise();

	// The contact normal depends on whether we're extending or compressing
	if (currentLen > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else
	{
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLen;
	}

	// Always use zero restitution (no bounciness)
	contact->restitution = 0;

	return 1;
}