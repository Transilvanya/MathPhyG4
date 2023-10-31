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

		//std::cout << "contact start ________________ \n\n";

		std::map<std::string, Particule*>::iterator it = objects.begin();
		while (it != objects.end())
		{


			std::map<std::string, Particule*>::iterator it2 = it;
			it2++;
			while (it2 != objects.end())
			{
				/*
				std::cout << it->second->GetName() << "\n";
				std::cout << "pos " << it->second->getPosition().getX() << " " << it->second->getPosition().getY() << " " << it->second->getPosition().getZ() << "\n";
				std::cout << "vit " << it->second->getVitesse().getX() << " " << it->second->getVitesse().getY() << " " << it->second->getVitesse().getZ() << "\n";
				std::cout << "vit " << it->second->getVitesse().getNorm() << "\n\n";

				std::cout << "\t" << it2->second->GetName() << "\n";
				std::cout << "\tpos " << it2->second->getPosition().getX() << " " << it2->second->getPosition().getY() << " " << it2->second->getPosition().getZ() << "\n";
				std::cout << "\tvit " << it2->second->getVitesse().getX() << " " << it2->second->getVitesse().getY() << " " << it2->second->getVitesse().getZ() << "\n";
				std::cout << "\tvit " << it2->second->getVitesse().getNorm() << "\n\n";
				*/



				Vector3D contactnormal = (it->second->getPosition() - it2->second->getPosition() );
				float dist = contactnormal.getNorm();

				Vector3D speeddif = (it->second->getVitesse() - it2->second->getVitesse());
				
				//std::cout << "\tdist " << dist << "\n";
				//std::cout << "\tspeed " << speeddif.getNorm()  << "\n";

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
					float DistSum = 2;
					//we assume the particule as a radius of 1
					if (dist <= DistSum && DistSum - dist > ContactPrecision)
					{
						//std::cout << "\tpenetration " << DistSum - dist << "\n";
						//std::cout << "\tcontact normal uniform " << contactnormal.getX() << " " << contactnormal.getY() << " " << contactnormal.getZ() << "\n";

						ParticleContact pc = ParticleContact(it->second, it2->second, 1, DistSum - dist, contactnormal);
						Contacts->push_back(pc);

						//std::cout << "\t\t\t\t\t\t contact particule \n";
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
