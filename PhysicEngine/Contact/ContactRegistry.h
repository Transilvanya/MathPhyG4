
#ifndef CONTACTREGISTRY_CLASS_H
#define CONTACTREGISTRY_CLASS_H


#include "../Particules/Particule.h"
#include "ParticleContact.h"

#include <list>
#include <iostream>
#include <map>
#include "ContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleRod.h"
#include "ParticleAnchor.h"

class ContactRegistry
{
private:
	std::list<ParticleContact> Contacts;

	std::map<std::string, ParticleLink*> LinkEntries;

	std::map<std::string, ParticleAnchor*> AnchorEntries;

	//max iter of contact
	unsigned int iteration;

	float ContactPrecision = 0.001;
public:

	
	unsigned int GetIteration() { return iteration; }

	//fill Contacts with the list of Contact
	bool AddContacts(std::map<std::string, Particule*> objects)
	{
		Contacts.clear();

		ContactGenerator c(objects);
		c.AddContact(&Contacts);




		std::map<std::string, ParticleLink*>::iterator it = LinkEntries.begin();
		// Iterate through the map and print the elements
		while (it != LinkEntries.end())
		{
			it->second->AddContact(&Contacts);
			it++;
		}

		//std::cout << " __________________ \n\n";

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

	void ApplyAnchors()
	{
		std::map<std::string, ParticleAnchor*>::iterator it2 = AnchorEntries.begin();
		// Iterate through the map and print the elements
		while (it2 != AnchorEntries.end())
		{
			it2->second->ApplyAnchor();
			it2++;
		}

	}











	//add and remove a particule from the 
	void CreateLink(Particule* p1, Particule* p2, std::string name)
	{
		ParticleLink* temp = new ParticleLink(p1, p2);

		if (LinkEntries.count(name))
		{
			std::cout << "already exist ParticuleLink " << name << "\n";
		}
		else
		{
			LinkEntries.emplace(name, temp);
		}


	}

	void CreateRod(Particule* p1, Particule* p2, std::string name, float lenght, bool iscable)
	{
		ParticleRod* temp = new ParticleRod(p1, p2, lenght, iscable);

		if (LinkEntries.count(name))
		{
			std::cout << "already exist ParticuleLink " << name << "\n";
		}
		else
		{
			//std::cout << "create link\n";
			LinkEntries.emplace(name, temp);
		}


	}

	void RemoveLink(std::string name)
	{
		if (LinkEntries.count(name))
		{
			delete(LinkEntries.find(name)->second);
			LinkEntries.erase(name);

		}
		else
		{
			std::cout << "coud not find ParticuleLink " << name << "\n";
		}
	}

	void CreateAnchor(Particule* p1, Vector3D p, std::string name, float lenght, bool iscable)
	{
		ParticleAnchor* temp = new ParticleAnchor(p1, p, lenght, iscable);

		if (AnchorEntries.count(name))
		{
			std::cout << "already exist ParticuleAnchor " << name << "\n";
		}
		else
		{
			//std::cout << "create link\n";
			AnchorEntries.emplace(name, temp);
		}


	}

	void RemoveAnchor(std::string name)
	{
		if (AnchorEntries.count(name))
		{
			delete(AnchorEntries.find(name)->second);
			AnchorEntries.erase(name);

		}
		else
		{
			std::cout << "coud not find ParticuleAnchor " << name << "\n";
		}
	}

	ParticleLink* GetLink(std::string nameObject, std::string nameForce)
	{
		ParticleLink* output = nullptr;

		if (LinkEntries.count(nameObject))
		{
			output = (LinkEntries.find(nameObject)->second);
		}
		else
		{
			std::cout << "coud not find ParticuleLink " << nameObject << "\n";
		}

		return output;
	}

	std::list<std::string> GetLinks()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, ParticleLink*>::iterator it = LinkEntries.begin();

		// Iterate through the map and print the elements
		while (it != LinkEntries.end())
		{
			output.push_back(it->first);
			++it;
		}



		return output;
	}

	ParticleAnchor* GetAnchor(std::string nameObject, std::string nameForce)
	{
		ParticleAnchor* output = nullptr;

		if (AnchorEntries.count(nameObject))
		{
			output = (AnchorEntries.find(nameObject)->second);
		}
		else
		{
			std::cout << "coud not find ParticuleLink " << nameObject << "\n";
		}

		return output;
	}

	std::list<std::string> GetAnchors()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, ParticleAnchor*>::iterator it = AnchorEntries.begin();

		// Iterate through the map and print the elements
		while (it != AnchorEntries.end())
		{
			output.push_back(it->first);
			++it;
		}



		return output;
	}
};


#endif
