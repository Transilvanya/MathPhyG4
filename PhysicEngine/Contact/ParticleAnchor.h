

#ifndef PARTICLEANCHOR_CLASS_H
#define PARTICLEANCHOR_CLASS_H

#include "../Particules/Particule.h"

class ParticleAnchor
{
public:
	Particule* particule;
	Vector3D point;
	float Length;
	bool isCable;

	ParticleAnchor(Particule* p0, Vector3D _point, float _Length, bool _isCable)
	{
		particule = p0;
		point = _point;
		Length = _Length;
		isCable = _isCable;
	}



	void ApplyAnchor()
	{

		//std::cout << "\t" << it2->second->GetName() << "\t";
		Vector3D contactnormal = (particule->getPosition() - point);
		float dist = contactnormal.getNorm();

		//std::cout << dist << " " << Length << "\n";

		if (dist > 0)
		{
			array<float, 3> temp = contactnormal.getUnitVector();
			contactnormal = Vector3D(temp.at(0), temp.at(1), temp.at(2));




			if (dist > Length)
			{
				//std::cout << dist << " " << Length << "\n";

				Vector3D temp0 = contactnormal * -1 * (dist - Length);

				particule->setPosition(particule->getPosition() + temp0);
			}

			if (dist <= Length && !isCable)
			{
			
				//std::cout << dist << " " << Length << "\n";

				Vector3D temp0 = contactnormal * (Length - dist);

				particule->setPosition(particule->getPosition() + temp0);
			}
		}
		

		//std::cout << "link\n";
	}

};




#endif // MATHPHYG4_PARTICLEROD_H
