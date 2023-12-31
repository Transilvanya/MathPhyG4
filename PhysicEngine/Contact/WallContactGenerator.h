

#ifndef MATHPHYG4_WALLCONTACT_H
#define MATHPHYG4_WALLCONTACT_H

#include "../Particules/Particule.h"
#include "WallContact.h"

#include <list>
#include <iostream>
#include <map>



class WallContactGenerator
{
public:
	float ContactPrecision = 0.001;

	std::map<std::string, Particule*> objects;
	std::map<std::string, Wall*> walls;
	

	WallContactGenerator(std::map<std::string, Particule*> _objects)
	{
		objects = _objects;
		walls.emplace("sol", Wall( Vector3D(-10, 0, -10), Vector3D(10, 0, -10), Vector3D(-10, 0, 10), Vector3D(10, 0, 10) ) );
	}

	virtual void AddContact(std::list<WallContact>* Contacts)
	{

		std::map<std::string, Wall*>::iterator it = walls.begin();
		while (it != walls.end())
		{


			std::map<std::string, Particule*>::iterator it2 = objects.begin();
			while (it2 != objects.end())
			{
				Vector3D contactnormal = (it->second->getPosition() - it2->second->getPosition());
				float dist = contactnormal.getNorm();

				Vector3D speeddif = (it->second->getVitesse() - it2->second->getVitesse());

				if (dist > 0)
				{
					array<float, 3> temp = contactnormal.getUnitVector();
					contactnormal = Vector3D(temp.at(0), temp.at(1), temp.at(2));
					float DistSum = 2;
					if (dist <= DistSum && DistSum - dist > ContactPrecision)
					{
						WallContact pc = WallContact(it->second, 1, DistSum - dist, contactnormal);
						Contacts->push_back(pc);
					}
				}

				++it2;
			}
			++it;
			//std::cout << "\n";
		}

	}

};



#endif // MATHPHYG4_PARTICLELINK_H
