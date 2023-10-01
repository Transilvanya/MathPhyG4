#include "MainManager.h"
#include "../PhysicEngine/PhysicEngine.h"
#include "../GraphicEngine/GraphicEngine.h"


void MainManager::Update()
{
	/* -- Systems -- */
	std::vector<ISystem*>::iterator it;

	for (it = _systems.begin(); it != _systems.end(); it++)
	{
		(*it)->Tick();
	}
	/* -- ------- -- */

	std::vector<Entity*>::iterator it2;

	for (it2 = _entities.begin(); it2 != _entities.end(); it2++)
	{
		if ((*it2)->Getdisplayenabled())
		{
			GraphicEngine::GetInstance()->AddElementToDisplay((*it2)->_GraphicObject);
		}
		if ((*it2)->Getphysicsenabled())
		{
			PhysicEngine::GetInstance()->AddElementToIntegrade((*it2)->_PhysicObject);
		}
	}
}

void MainManager::Init()
{
	TimeSystem* s = new TimeSystem();

	AddSystem(s);
}

Entity* MainManager::GetEntity(std::string name)
{
	Entity* result = nullptr;

	std::vector<Entity*>::iterator it;
	for (it = _entities.begin(); it != _entities.end(); it++)
	{

		if ((*it)->GetName().compare(name) == 0)
		{
			result = *it;
			break;
		}
	}

	return result;
}

void MainManager::AddEntity(Entity* entity)
{
	_entities.push_back(entity);
}

void MainManager::RemoveEntity(std::string name)
{
	Entity* result = nullptr;

	std::vector<Entity*>::iterator it;
	int i = 0;
	for (it = _entities.begin(); it != _entities.end(); it++, i++)
	{

		if ((*it)->GetName().compare(name) == 0)
			break;
	}
	_entities.erase(_entities.begin() + i);
}

ISystem* MainManager::GetSystem(std::string name)
{
	int factor = 1;
	int total = 0;
	for (int i = 0; i < name.length(); i++)
	{
		total += factor * name[i];
		factor *= 10;
	}

	ISystem* result = nullptr;

	std::vector<ISystem*>::iterator it;
	for (it = _systems.begin(); it != _systems.end(); it++)
	{

		if ((*it)->GetName() == total)
		{
			result = *it;
			break;
		}
	}

	return result;
}

void MainManager::AddSystem(ISystem* system)
{
	_systems.push_back(system);
}

void MainManager::RemoveSystem(std::string name)
{
	int factor = 1;
	int total = 0;
	for (int i = 0; i < name.length(); i++)
	{
		total += factor * name[i];
		factor *= 10;
	}


	std::vector<ISystem*>::iterator it;
	int i = 0;
	for (it = _systems.begin(); it != _systems.end(); it++, i++)
	{
		if ((*it)->GetName() == total)
		{
			break;
		}
	}
	_systems.erase(_systems.begin() + i);
}
