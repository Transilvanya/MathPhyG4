

#ifndef WALLCONTACT_CLASS_H
#define WALLCONTACT_CLASS_H

#include "../Particules/Particule.h"

class WallContact
{

private:
	Particule* particule;

	// 0 - 1
	// elasticity of collision
	float restitution;

	//distance of penetration of contact, aka lenght where overlap
	float penetration;


	Vector3D contactNormal;


public:

	WallContact(Particule* p1, float _restitution, float _penetration, Vector3D _contactNormal)
	{
		particule = p1;
		restitution = _restitution;
		penetration = _penetration;
		contactNormal = _contactNormal;
	}


	void SolveContact()
	{

		Vector3D temp0 = contactNormal * penetration;

		particule->setPosition(particule->getPosition() + temp0);
		
		/* --------------------------------------- */

		float k = (restitution + 1) * (particule->getVitesse() & contactNormal);
		particule->setVitesse(particule->getVitesse() - contactNormal * k );

	}


};

#endif