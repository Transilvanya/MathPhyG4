#include "ParticleContact.h"


void ParticleContact::resolve(float duration)
{
	resolveVelocity();
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity() const
{
	Vector3D relativeVelocity = particule[0]->getVitesse();
	if (particule[1])
	{
		relativeVelocity = relativeVelocity - particule[1]->getVitesse();
	}
	return relativeVelocity & contactNormal;
}

//Handle impulse for this collision
void ParticleContact::resolveVelocity() 
{
	int k = 0;
	Vector3D vRel = particule[0]->getVitesse() - particule[1]->getVitesse();
	k = vRel * (restitution+1) & contactNormal;
	k = k / (particule[0]->getInverseMasse() + particule[1]->getInverseMasse());

}

void ParticleContact::resolveInterpenetration()
{
	int deltaA = particule[1]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());
	int deltaB = -(particule[0]->getMasse()) / (particule[0]->getMasse() + particule[1]->getMasse());


	particule[0]->setPosition(particule[0]->getPostion() + (contactNormal * deltaA * penetration));
	particule[1]->setPosition(particule[1]->getPostion() + (contactNormal * deltaB * penetration));
}