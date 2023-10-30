#ifndef CONTACTGENERATOR_CLASS_H
#define CONTACTGENERATOR_CLASS_H


#include "../Particules/Particule.h"
#include "ParticleContact.h"

#include <list>
#include <iostream>
#include <map>


class ContactGenerator
{
public:
	float ContactPrecision = 0.001;

	std::map<std::string, Particule*> objects;

	ContactGenerator(std::map<std::string, Particule*> _objects)
	{
		objects = _objects;
	}

	//fill Contacts for the Particules
	virtual void AddContact(std::list<ParticleContact>* Contacts)
	{

		//std::cout << "contact start\n";

		std::map<std::string, Particule*>::iterator it = objects.begin();
		while (it != objects.end())
		{
			//std::cout << it->second->GetName() << "\n";
			std::map<std::string, Particule*>::iterator it2 = it;
			it2++;
			while (it2 != objects.end())
			{
				//std::cout << "\t" << it2->second->GetName() << "\t";
				Vector3D contactnormal = (it->second->getPosition() - it2->second->getPosition());
				float dist = contactnormal.getNorm();


				if (dist > 0)
				{
					array<float, 3> temp = contactnormal.getUnitVector();
					contactnormal = Vector3D(temp.at(0), temp.at(1), temp.at(2));
					/*
					std::cout << dist << "\t";
					std::cout << contactnormal.getX() << " " << contactnormal.getY() << " " << contactnormal.getZ();
					std::cout << "\n";
					*/
					//distance between the center of the 2 object
					float DistSum = 1 + 1;
					//we assume the particule as a radius of 1
					if (dist <= DistSum && DistSum - dist > ContactPrecision)
					{
						ParticleContact pc = ParticleContact(it->second, it2->second, 1, DistSum - dist, contactnormal);
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


#endif
