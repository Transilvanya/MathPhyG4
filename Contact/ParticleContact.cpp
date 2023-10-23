#include "ParticleContact.h"


void ParticleContact::resolve(float duration)
{
	printf("resolve");
	resolveVelocity();
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity() const
{
	Vector3D relativeVelocity = particule[0]->getVitesse();
	printf("1");
	if (particule[1])
	{
		printf("2");
		Vector3D resultat = (relativeVelocity - particule[1]->getVitesse());
		printf("bite");

	}
	printf("3");
	return relativeVelocity.scalar(contactNormal);
}

//Handle impulse for this collision
void ParticleContact::resolveVelocity() 
{
	float k = 0;
	Vector3D vRel = particule[0]->getVitesse() - particule[1]->getVitesse();
	k = (vRel * (restitution+1)).scalar(contactNormal);
	k = k / (particule[0]->getInverseMasse() + particule[1]->getInverseMasse());

}

void ParticleContact::resolveInterpenetration()
{
	int deltaA = particule[1]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());
	int deltaB = -(particule[0]->getMasse()) / (particule[0]->getMasse() + particule[1]->getMasse());


	particule[0]->setPosition(particule[0]->getPosition() + (contactNormal * deltaA * penetration));
	particule[1]->setPosition(particule[1]->getPosition() + (contactNormal * deltaB * penetration));
}