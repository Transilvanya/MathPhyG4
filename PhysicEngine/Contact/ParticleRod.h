#pragma once
#ifndef MATHPHYG4_PARTICLEROD_H
#define MATHPHYG4_PARTICLEROD_H
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
	
	//generate contact if not length
	float Length = 1;
	bool isCable;

	ParticleRod(Particule* p0, Particule* p1, float _Length, bool _isCable) : ParticleLink(p0,p1)
	{
		particule[0] = p0;
		particule[1] = p1;
		if (_Length > 0)
		{
			Length = _Length;
		}
		
		isCable = _isCable;
	}

	void AddContact(std::list<ParticleContact>* Contacts)
	{
		Vector3D contactnormal = (particule[0]->getPosition() - particule[1]->getPosition());
		float dist = contactnormal.getNorm();

		array<float, 3> temp = contactnormal.getUnitVector();
		contactnormal = Vector3D(temp.at(0), temp.at(1), temp.at(2));


		//>0?
		std::cout << "\t\t" << contactnormal.getX() << " " << contactnormal.getY() << " " << contactnormal.getZ() << "\n";
		//Selon si la distance des particule est plus petite ou plus grande que la
		//longueur de la tige, la normal et la pénétration seront inversées.

		//penetration toujours positive, normal doit etre inversé

		if (dist > Length && Length - dist < -0.01f)
		{
		
			ParticleContact pc = ParticleContact(particule[0], particule[1], 0, Length - dist, contactnormal);
			Contacts->push_back(pc);






			std::cout << particule[0]->getPosition().getX() << " " << particule[0]->getPosition().getY() << " " << particule[0]->getPosition().getZ() << "\n";
			std::cout << particule[1]->getPosition().getX() << " " << particule[1]->getPosition().getY() << " " << particule[1]->getPosition().getZ() << "\n";
			std::cout << dist << " " << Length << " " << Length - dist << "\n";
			std::cout << "\t\t" << contactnormal.getX() << " " << contactnormal.getY() << " " << contactnormal.getZ() << "\n";

		}


		//working fine
		if (dist <= Length && !isCable && dist > 0)
		{
			ParticleContact pc = ParticleContact(particule[0], particule[1], 0, Length - dist, contactnormal);
			Contacts->push_back(pc);
		}

		std::cout << "\n";
	}
};



#endif // MATHPHYG4_PARTICLEROD_H
