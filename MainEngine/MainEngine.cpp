#include "MainEngine.h"
#include "../PhysicEngine/PhysicEngine.h"
#include "../GraphicEngine/GraphicEngine.h"


void MainEngine::Tick()
{

	// Get an iterator pointing to the first element in the map
	std::map<std::string, ISystem*>::iterator it = _systems.begin();

	// Iterate through the map and print the elements
	while (it != _systems.end())
	{
		it->second->Tick();
		++it;
	}
}

void MainEngine::UpdateEntityPostion()
{
	// Get an iterator pointing to the first element in the map
	std::map<std::string, Entity*>::iterator it = _entities.begin();

	// Iterate through the map and print the elements
	while (it != _entities.end())
	{
		Vector3D temp = it->second->_PhysicObject->getDeltaPosition();
		it->second->_GraphicObject->SetMvt(temp.getX(), temp.getY(), temp.getZ());
		it->second->_GraphicObject->ElementToUpdate();
		
		++it;


	}

	// Get an iterator pointing to the first element in the map
	std::map<std::string, EntityRB*>::iterator it2 = _entitiesRB.begin();

	// Iterate through the map and print the elements
	while (it2 != _entitiesRB.end())
	{
		Matrice34 m = it2->second->_PhysicObject->GettransformMatrix();
		it2->second->_GraphicObject->SetMtransform(m);
	
		++it2;
	}
}

MainEngine::~MainEngine()
{
	_systems.empty();
	_entities.empty();
}

MainEngine::MainEngine()
{
	Init();
}

void MainEngine::Init()
{
	TimeSystem* s = new TimeSystem();

	AddSystem(s);
}

Entity* MainEngine::GetEntity(std::string name)
{

	if (_entities.count(name))
		return _entities.find(name)->second;
	else
	{
		std::cout << "coud not get Entity " << name << "\n";
		return nullptr;
	}
}

void MainEngine::CreateEntity(Particule* PO, GraphicObject* GO, std::string name)
{

	Entity* temp = new Entity(PO, GO, name);
	_entities.emplace(name, temp);
}

void MainEngine::RemoveEntity(std::string name)
{
	if (_entities.count(name))
	{
		Entity* temp = _entities.find(name)->second;
		_entities.erase(name);
		delete(temp);
	}
	else
	{
		std::cout << "coud not remove Entity " << name << "\n";
	}

}


void MainEngine::CreateEntityRB(RigidBody* RB, GraphicObjectwithTexture* GO, std::string name)
{

	EntityRB* temp = new EntityRB(RB, GO, name);
	_entitiesRB.emplace(name, temp);
}


EntityRB* MainEngine::GetEntityRB(std::string name)
{

	if (_entitiesRB.count(name))
		return _entitiesRB.find(name)->second;
	else
	{
		std::cout << "coud not get EntityRB " << name << "\n";
		return nullptr;
	}
}

void MainEngine::RemoveEntityRB(std::string name)
{
	if (_entitiesRB.count(name))
	{
		EntityRB* temp = _entitiesRB.find(name)->second;
		_entitiesRB.erase(name);
		delete(temp);
	}
	else
	{
		std::cout << "coud not remove EntityRB " << name << "\n";
	}
}

ISystem* MainEngine::GetSystem(std::string name)
{

	if (_systems.count(name))
		return _systems.find(name)->second;
	else
	{
		std::cout << "coud not get System " << name << "\n";
		return nullptr;
	}
}

void MainEngine::AddSystem(ISystem* system)
{
	_systems.emplace(system->getName(), system);
}

void MainEngine::RemoveSystem(std::string name)
{

	if (_systems.count(name))
	{
		ISystem* temp = _systems.find(name)->second;
		_systems.erase(name);
		delete(temp);
	}
	else
	{
		std::cout << "coud not remove System " << name << "\n";
	}

}
