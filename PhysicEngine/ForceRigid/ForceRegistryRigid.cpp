#include "ForceRegistryRigid.h"

void ForceRegistryRigid::AddRigidBody(RigidBody* object)
{
	RigidBodyEntry temp;
	temp.rigidbody = object;
	ForceEntries.emplace(object->getObjectName(), temp);
}

void ForceRegistryRigid::RemoveRigidBody(std::string name)
{
	if (ForceEntries.count(name))
	{

		std::list<std::string> forcelist = GetForcesOfRigidBody(name);

		std::list<std::string>::iterator it = forcelist.begin();

		// Iterate through the map and print the elements
		while (it != forcelist.end())
		{
			RemoveForceFromRigidBody(name, *it);
			++it;
		}

		ForceEntries.erase(name);
	}
	else
	{
		std::cout << "coud not remove ForceEntries " << name << "\n";
	}
}


void ForceRegistryRigid::AddForceToRigidBodyAtPoint(RigidBody* object, IForceRigid* force, Vector3D ApplicationPoint, std::string name, bool _isGlobalCoordinate)
{
	if (ForceEntries.count(object->getObjectName()))
	{
		if (ForceEntries.find(object->getObjectName())->second.forces.count(name))
		{
			std::cout << "A force named " << name << " already existe in rigidbody " << object->getObjectName() << "\n";
		}
		else
		{
			ForceEntries.find(object->getObjectName())->second.forces.emplace(name, ForceApplication{ force, ApplicationPoint, false, _isGlobalCoordinate });
		}
	}
	else
	{
		AddRigidBody(object);
		ForceEntries.find(object->getObjectName())->second.forces.emplace(name, ForceApplication{ force, ApplicationPoint, false, _isGlobalCoordinate });
	}

}

void ForceRegistryRigid::AddForceToRigidBody(RigidBody* object, IForceRigid* force, std::string name)
{
	if (ForceEntries.count(object->getObjectName()))
	{
		if (ForceEntries.find(object->getObjectName())->second.forces.count(name))
		{
			std::cout << "A force named " << name << " already existe in rigidbody " << object->getObjectName() << "\n";
		}
		else
		{
			ForceEntries.find(object->getObjectName())->second.forces.emplace(name, ForceApplication{ force, Vector3D(0,0,0), true, false });
		}
	}
	else
	{
		AddRigidBody(object);
		ForceEntries.find(object->getObjectName())->second.forces.emplace(name, ForceApplication{ force, Vector3D(0,0,0), true, false });
	}
}

void ForceRegistryRigid::RemoveForceFromRigidBody(std::string nameObject, std::string nameForce)
{
	if (ForceEntries.count(nameObject))
	{
		if (ForceEntries.find(nameObject)->second.forces.count(nameForce))
		{
			//std::cout << nameObject <<" remove " << nameForce << "\n";
			IForceRigid* temp = ForceEntries.find(nameObject)->second.forces.find(nameForce)->second.force;
			delete(temp);
			ForceEntries.find(nameObject)->second.forces.erase(nameForce);

		}
		else
		{
			std::cout << "coud not remove Force " << nameForce << "\n";
		}
	}
	else
	{
		std::cout << "coud not find ForceEntries " << nameObject << "\n";
	}
}

IForceRigid* ForceRegistryRigid::GetForce(std::string nameObject, std::string nameForce)
{
	IForceRigid* output = nullptr;

	if (ForceEntries.count(nameObject))
	{
		if (ForceEntries.find(nameObject)->second.forces.count(nameObject))
		{
			output = ForceEntries.find(nameObject)->second.forces.find(nameObject)->second.force;
		}
		else
		{
			std::cout << "coud not find Force " << nameForce << "\n";
		}
	}
	else
	{
		std::cout << "coud not find ForceEntries " << nameObject << "\n";
	}

	return output;
}

std::list<std::string> ForceRegistryRigid::GetForcesOfRigidBody(std::string name)
{
	std::list<std::string> output;

	if (ForceEntries.count(name))
	{
		std::map<std::string, ForceApplication>::iterator it = ForceEntries.find(name)->second.forces.begin();

		while (it != ForceEntries.find(name)->second.forces.end())
		{
			output.push_back(it->first);
			++it;
		}
	}
	else
	{
		std::cout << "coud not find ForceEntries " << name << "\n";
	}

	return output;
}



void ForceRegistryRigid::ApplyForces()
{
	std::map<std::string, RigidBodyEntry>::iterator it = ForceEntries.begin();

	while (it != ForceEntries.end())
	{
		if (true)
		{
			Vector3D TotalForce = Vector3D(0, 0, 0);

			std::list<std::string> ForcetoRemove;

			std::map<std::string, ForceApplication>::iterator it2 = it->second.forces.begin();
			while (it2 != it->second.forces.end())
			{
				if (it2->second.force->IsForceApplied())
				{
					IForceRigid::OutValues outValue = it2->second.force->ApplyForce(it->second.rigidbody);

					if (it2->second.IsGlobalForce) {
						it->second.rigidbody->AddForce(outValue.outVector);
					}
					else {
						if (it2->second.isGlobalCoordinate) {
							it->second.rigidbody->AddForcePoint(outValue.outVector, it2->second.ApplicationPoint);
						}
						else {
							it->second.rigidbody->AddForceAtBodyPoint(outValue.outVector, it2->second.ApplicationPoint);
						}
					}
				}
				++it2;
			}

			if (ForcetoRemove.size() > 0)
			{
				std::list<std::string>::iterator it3;
				for (it3 = ForcetoRemove.begin(); it3 != ForcetoRemove.end(); it3++)
				{
					std::cout << "Force broke on rigidbody : " << it->second.rigidbody->getObjectName() << " force : " << it3->c_str() << "\n";
					RemoveForceFromRigidBody(it->second.rigidbody->getObjectName(), it3->c_str());
				}
			}
		}
		++it;
	}
}

void ForceRegistryRigid::AddForceGravityToRigidBody(RigidBody* rigidbody, std::string forcename)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else
	{
		ForceGravity* f = new ForceGravity;
		AddForceToRigidBody(rigidbody, f, forcename);
	}
}


void ForceRegistryRigid::AddForceSimpleToRigidBody(Vector3D forcevector, RigidBody* rigidbody, std::string forcename)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else 
	{
		SimpleForce *f = new SimpleForce(forcevector);
		AddForceToRigidBody(rigidbody, f, forcename);
	}
}

void ForceRegistryRigid::AddForceSimpleToRigidBodyAtPoint(Vector3D forcevector, RigidBody* rigidbody, std::string forcename, Vector3D ApplicationPoint, bool _isGlobalCoordinate)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else
	{
		SimpleForce* f = new SimpleForce(forcevector);
		AddForceToRigidBodyAtPoint(rigidbody, f, ApplicationPoint, forcename, _isGlobalCoordinate);
	}
}

void ForceRegistryRigid::AddForceDragToRigidBody(float k1, float k2, RigidBody* rigidbody, std::string forcename)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else 
	{
		ForceDrag* f = new ForceDrag(k1, k2);
		AddForceToRigidBody(rigidbody, f, forcename);
	}
}

void ForceRegistryRigid::AddForceBuoyancyToRigidBody(float liquidheight, float liquiddensity, RigidBody* rigidbody, std::string forcename)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else
	{
		ForceBuoyancy* f = new ForceBuoyancy(liquidheight, liquiddensity);
		AddForceToRigidBody(rigidbody, f, forcename);
	}
}

void ForceRegistryRigid::AddForceSpringFixedToRigidBody(Vector3D anchor, float k, float l0, float maxlength, bool bungeespring, RigidBody* rigidbody, Vector3D _Anchor, std::string forcename)
{
	if (rigidbody == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else
	{
		ForceSpringFixed* f = new ForceSpringFixed(anchor, _Anchor, k, l0, maxlength, bungeespring);
		AddForceToRigidBody(rigidbody, f, forcename);
	}
}

void ForceRegistryRigid::AddForceSpringToRigidBody(float k, float l0, float maxlength, bool bungeespring, RigidBody* rigidbody1, RigidBody* rigidbody2, Vector3D _Anchor1, Vector3D _Anchor2, std::string forcename)
{
	if(rigidbody1 == NULL || rigidbody2 == NULL)
	{
		std::cout << "Error Creation Force, a rigidbody is incorrect\n";
	}
	else
	{
		ForceSpring* f1 = new ForceSpring(rigidbody1, _Anchor1, _Anchor2, k, l0, maxlength, bungeespring);
		ForceSpring* f2 = new ForceSpring(rigidbody2, _Anchor2, _Anchor1, k, l0, maxlength, bungeespring);

		AddForceToRigidBody(rigidbody1, f2, forcename);
		AddForceToRigidBody(rigidbody2, f1, forcename);
	}
}





