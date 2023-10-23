#pragma once
#ifndef MATHPHYG4_PARTICLEROD_H
#define MATHPHYG4_PARTICLEROD_H
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
	
	//generate contact if not length
	float Length;
	bool isCable;

	ParticleRod(Particule* p0, Particule* p1, float _Length, bool _isCable) : ParticleLink(p0,p1)
	{
		particule[0] = p0;
		particule[1] = p1;
		Length = _Length;
		isCable = _isCable;
	}

	void ApplyLink()
	{

		
		//std::cout << "\t" << it2->second->GetName() << "\t";
		Vector3D contactnormal = (particule[0]->getPosition() - particule[1]->getPosition());
		float dist = contactnormal.getNorm();

		//std::cout << dist << " " << Length << "\n";

		if (dist > 0)
		{
			array<float, 3> temp = contactnormal.getUnitVector();
			contactnormal = Vector3D(temp.at(0), temp.at(1), temp.at(2));
		

			

			if (dist > Length)
			{
				float weight0 = particule[0]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());
				float weight1 = particule[1]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());

				//std::cout << dist << " " << Length << "\n";

				Vector3D temp0 = contactnormal * -weight0 * (dist-Length);
				Vector3D temp1 = contactnormal * weight1 * (dist-Length);



				particule[0]->setPosition(particule[0]->getPosition() + temp0);
				particule[1]->setPosition(particule[1]->getPosition() + temp1);
			}

			if (dist <= Length && !isCable)
			{
				float weight0 = particule[0]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());
				float weight1 = particule[1]->getMasse() / (particule[0]->getMasse() + particule[1]->getMasse());

				//std::cout << dist << " " << Length << "\n";

				Vector3D temp0 = contactnormal * weight0 * (Length - dist);
				Vector3D temp1 = contactnormal * -weight1 * (Length - dist);

				particule[0]->setPosition(particule[0]->getPosition() + temp0);
				particule[1]->setPosition(particule[1]->getPosition() + temp1);
			}
		}


		//std::cout << "link\n";
	}
};



#endif // MATHPHYG4_PARTICLEROD_H
