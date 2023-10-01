
#ifndef MAINMANAGER_CLASS_H
#define MAINMANAGER_CLASS_H

#include "TimeSystem.h"
#include <vector>
#include <string>
#include "Entity.h"


class MainManager
{

public :

	static MainManager* _mainmanagerptr;

	static MainManager* GetInstance()
	{
		if (_mainmanagerptr == nullptr)
		{
			_mainmanagerptr = new MainManager();
		}

		return _mainmanagerptr;
	}

	MainManager() {}
	void Init();
	void Update();

	ISystem* GetSystem(std::string name);
	void AddSystem(ISystem* system);
	void RemoveSystem(std::string name);

	Entity* GetEntity(std::string name);
	void AddEntity(Entity* entity);
	void RemoveEntity(std::string name);
	

private:

	std::vector<ISystem*> _systems;
	std::vector<Entity*> _entities;



};

//MainManager* MainManager::_mainmanager = NULL;

#endif

