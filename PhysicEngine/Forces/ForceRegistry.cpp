#include "ForceRegistry.h"

ForceRegistry::~ForceRegistry()
{
	ParticuleEntries.empty();
}

void ForceRegistry::ApplyForces()
{
	// Get an iterator pointing to the first element in the map
	std::map<std::string, ParticuleEntry>::iterator it = ParticuleEntries.begin();

	// Iterate through the map and print the elements
	while (it != ParticuleEntries.end())
	{
		if (true) //it->second.particule->IsPhysicsEnabled())
		{
			//std::cout << "______\n" << it->second.particule->getName() << "\n";
			Vector3D TotalForce = Vector3D(0, 0, 0);


			std::list<std::string> ForcetoRemove;


			std::map<std::string, IForce*>::iterator it2 = it->second.forces.begin();
			while (it2 != it->second.forces.end())
			{
				if (it2->second->IsForceApplied())
				{
					IForce::OutValues outvalue = it2->second->ApplyForce(it->second.particule);
					TotalForce = TotalForce + outvalue.outvector;


					if (outvalue.removeforce)
					{
						ForcetoRemove.push_back(it2->first);
					}

					//std::cout<<"\t" << it2->second->getType() << " "<< outvalue.removeforce << "\n";
					//std::cout <<"\t" << outvalue.outvector.getX() << " " << outvalue.outvector.getY() << " " << outvalue.outvector.getZ() << "\n";

				}
				++it2;
			}

			//std::cout << TotalForce.getX() << " " << TotalForce.getY() << " " << TotalForce.getZ() << "\n\n";

			it->second.particule->setForce(TotalForce);




			if (ForcetoRemove.size() > 0)
			{
				//std::cout << " _ ______  Force To Remove\n";
				std::list<std::string>::iterator it3;
				for (it3 = ForcetoRemove.begin(); it3 != ForcetoRemove.end(); it3++)
				{
					std::cout << "Force broke on particule : " << it->second.particule->GetName() << " force : " << it3->c_str() << "\n";
					RemoveForceFromParticule(it->second.particule->GetName(), it3->c_str());
				}
				//std::cout << "\n";
			}

		}
		++it;
	}

	//std::cout << "________________\n\n";
}

void ForceRegistry::AddParticule(Particule* object)
{
	ParticuleEntry temp;
	temp.particule = object;
	ParticuleEntries.emplace(object->GetName(), temp);
}
void ForceRegistry::RemoveParticule(std::string name)
{
	if (ParticuleEntries.count(name))
	{

		std::list<std::string> forcelist = GetForcesOfParticule(name);

		std::list<std::string>::iterator it = forcelist.begin();

		// Iterate through the map and print the elements
		while (it != forcelist.end())
		{
			RemoveForceFromParticule(name, *it);
			++it;
		}

		ParticuleEntries.erase(name);
	}
	else
	{
		std::cout << "coud not remove ParticuleEntry " << name << "\n";
	}
}

void ForceRegistry::AddForceToParticule(Particule* object, IForce* force, std::string name)
{
	if (ParticuleEntries.count(object->GetName()))
	{
		if (ParticuleEntries.find(object->GetName())->second.forces.count(name))
		{
			std::cout << "A force named " << name << " already existe in particule " << object->GetName() << "\n";
		}
		else
		{
			ParticuleEntries.find(object->GetName())->second.forces.emplace(name, force);
		}
	}
	else
	{
		AddParticule(object);
		ParticuleEntries.find(object->GetName())->second.forces.emplace(name, force);
	}
}
void ForceRegistry::RemoveForceFromParticule(std::string nameObject, std::string nameForce)
{
	if (ParticuleEntries.count(nameObject))
	{
		if (ParticuleEntries.find(nameObject)->second.forces.count(nameForce))
		{
			//std::cout << nameObject <<" remove " << nameForce << "\n";
			IForce* temp = ParticuleEntries.find(nameObject)->second.forces.find(nameForce)->second;
			delete(temp);
			ParticuleEntries.find(nameObject)->second.forces.erase(nameForce);

		}
		else
		{
			std::cout << "coud not remove Force " << nameForce << "\n";
		}
	}
	else
	{
		std::cout << "coud not find ParticuleEntry " << nameObject << "\n";
	}
}

IForce* ForceRegistry::GetForce(std::string nameObject, std::string nameForce)
{
	IForce* output = nullptr;

	if (ParticuleEntries.count(nameObject))
	{
		if (ParticuleEntries.find(nameObject)->second.forces.count(nameForce))
		{
			output = ParticuleEntries.find(nameObject)->second.forces.find(nameForce)->second;
		}
		else
		{
			std::cout << "coud not find Force " << nameForce << "\n";
		}
	}
	else
	{
		std::cout << "coud not find ParticuleEntry " << nameObject << "\n";
	}

	return output;
}

std::list<std::string> ForceRegistry::GetForcesOfParticule(std::string name)
{
	std::list<std::string> output;


	if (ParticuleEntries.count(name))
	{


		// Get an iterator pointing to the first element in the map
		std::map<std::string, IForce*>::iterator it = ParticuleEntries.find(name)->second.forces.begin();

		// Iterate through the map and print the elements
		while (it != ParticuleEntries.find(name)->second.forces.end())
		{
			output.push_back(it->first);
			++it;
		}
	}
	else
	{
		std::cout << "coud not find ParticuleEntry " << name << "\n";
	}



	return output;

}



void ForceRegistry::AddForceGravityToParticule(Particule* particule, std::string forcename)
{
	if (particule == NULL)
	{
		std::cout << "Error Creation Force, a particule is incorrect\n";
	}
	ForceGravity* f = new ForceGravity;
	AddForceToParticule(particule, f, forcename);
}

void ForceRegistry::AddForceDragToParticule(float k1, float k2, Particule* particule, std::string forcename)
{
	if (particule == NULL)
	{
		std::cout << "Error Creation Force, a particule is incorrect\n";
	}
	ForceDrag* f = new ForceDrag(k1, k2);
	AddForceToParticule(particule, f, forcename);
}

void ForceRegistry::AddForceBuoyancyToParticule(float liquidjheight, float liquiddensity, Particule* particule, std::string forcename)
{
	if (particule == NULL)
	{
		std::cout << "Error Creation Force, a particule is incorrect\n";
	}
	ForceBuoyancy* f = new ForceBuoyancy(liquidjheight, liquiddensity);
	AddForceToParticule(particule, f, forcename);
}

void ForceRegistry::AddForceSpringFixedToParticule(Vector3D anchor, float k, float l0, float maxlength, bool bungeespring, Particule* particule, std::string forcename)
{
	if (particule == NULL)
	{
		std::cout << "Error Creation Force, a particule is incorrect\n";
	}
	ForceSpringFixed* f = new ForceSpringFixed(anchor, k, l0, maxlength, bungeespring);
	AddForceToParticule(particule, f, forcename);
}

void ForceRegistry::AddForceSpringToParticule(float k, float l0, float maxlength, bool bungeespring, Particule* particule1, Particule* particule2, std::string forcename)
{
	if (particule1 == NULL || particule2 == NULL )
	{
		std::cout << "Error Creation Force, a particule is incorrect\n";
	}
	ForceSpring* f1 = new ForceSpring(particule2, k, l0, maxlength, bungeespring);
	ForceSpring* f2 = new ForceSpring(particule1, k, l0, maxlength, bungeespring);

	AddForceToParticule(particule1, f1, forcename);
	AddForceToParticule(particule2, f2, forcename);

}

