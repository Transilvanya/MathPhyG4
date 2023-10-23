
#ifndef CONTACTREGISTRY_CLASS_H
#define CONTACTREGISTRY_CLASS_H


#include "../Particules/Particule.h"
#include "ParticleContact.h"

#include <list>
#include <iostream>


class ContactRegistry
{
private:
	std::list<ParticleContact> Contacts;


	//max iter of contact
	unsigned int iteration;

	float ContactPrecision = 0.001;
public:

	
	unsigned int GetIteration() { return iteration; }

	//fill Contacts with the list of Contact
	bool DetectContact(std::map<std::string, Particule*> objects)
	{
		Contacts.clear();

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
						ParticleContact pc = ParticleContact(it->second, it2->second, 0, DistSum - dist, contactnormal);
						Contacts.push_back(pc);
					}
				}
				
				++it2;
			}
			++it;
			//std::cout << "\n";
		}

		/*
		std::cout <<"_____  \n" << Contacts.size() << "\n";

		std::list<ParticleContact>::iterator it3;
		for (it3 = Contacts.begin(); it3 != Contacts.end(); it3++)
		{
			std::cout << "- " << it3->write() << "\n";
		}
		std::cout << "contact end\n\n";
		*/

		return Contacts.size() != 0;
	}


	void SolveContact()
	{
		std::list<ParticleContact>::iterator it;
		for (it = Contacts.begin(); it != Contacts.end(); it++)
		{
			it->SolveContact();
		}
	}
};


#endif
