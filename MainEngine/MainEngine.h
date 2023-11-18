
#ifndef MAINMANAGER_CLASS_H
#define MAINMANAGER_CLASS_H

#include "TimeSystem.h"
#include <vector>
#include <string>
#include "Entity.h"
#include <map>
#include <list>


class MainEngine
{

public :

	static MainEngine* _mainmanagerptr;

	static MainEngine* GetInstance()
	{
		if (_mainmanagerptr == nullptr)
		{
			_mainmanagerptr = new MainEngine();
		}

		return _mainmanagerptr;
	}

	~MainEngine();

	MainEngine();
	void Init();
	void Tick();
	
	void UpdateEntityPostion();

	ISystem* GetSystem(std::string name);
	void AddSystem(ISystem* system);
	void RemoveSystem(std::string name);

	Entity* GetEntity(std::string name);
	void CreateEntity(Particule* PO, GraphicObject* GO, std::string name);
	void RemoveEntity(std::string name);

	EntityRB* GetEntityRB(std::string name);
	void CreateEntityRB(RigidBody* RB, GraphicObjectwithTexture* GO, std::string name);
	void RemoveEntityRB(std::string name);

	std::list<std::string> GetSystems()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, ISystem*>::iterator it = _systems.begin();

		// Iterate through the map and print the elements
		while (it != _systems.end())
		{
			output.push_back(it->first);
			++it;
		}

		return output;

	}

	std::list<std::string> GetEntities()
	{
		std::list<std::string> output;
		
		// Get an iterator pointing to the first element in the map
		std::map<std::string, Entity*>::iterator it = _entities.begin();

		// Iterate through the map and print the elements
		while (it != _entities.end())
		{
			output.push_back(it->first);

			++it;
		}
		
		return output;

	}

	std::list<std::string> GetEntitiesRB()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, EntityRB*>::iterator it = _entitiesRB.begin();

		// Iterate through the map and print the elements
		while (it != _entitiesRB.end())
		{
			output.push_back(it->first);

			++it;
		}

		return output;

	}

private:

	std::map<std::string, ISystem*> _systems;
	std::map<std::string, Entity*> _entities;
	std::map<std::string, EntityRB*> _entitiesRB;


};


#endif

