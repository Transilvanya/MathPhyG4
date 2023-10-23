
#ifndef LINKREGISTRY_CLASS_H
#define LINKREGISTRY_CLASS_H


#include "../Particules/Particule.h"
#include "ParticleContact.h"
#include "ParticleLink.h"
#include "ParticleRod.h"

#include <map>
#include <iostream>


class LinkRegistry
{
	std::map<std::string, ParticleLink*> LinkEntries;

public:
	/* for every particule in the registry, apply the sum of all the forces */
	void SolveLink()
	{
		

		std::map<std::string, ParticleLink*>::iterator it = LinkEntries.begin();

		// Iterate through the map and print the elements
		while (it != LinkEntries.end())
		{
			it->second->ApplyLink();
			it++;
		}
	}

	//add and remove a particule from the 
	void CreateLink(Particule* p1, Particule* p2, std::string name)
	{
		ParticleLink* temp = new ParticleLink(p1,p2);

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
};


#endif
