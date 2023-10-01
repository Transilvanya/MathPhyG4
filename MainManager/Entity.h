
#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "../PhysicEngine/PhysicObject.h"
#include "../GraphicEngine/GraphicObject.h"
#include <string>

class Entity
{
private:
	std::string _name = "default";

	bool displayenabled = false;
	bool physicsenabled = false;

public:

	Entity(PhysicObject* PO, GraphicObject* GO, std::string name)
	{
		_name = name;
		_PhysicObject = PO;
		_GraphicObject = GO;
	}

	PhysicObject* _PhysicObject;
	GraphicObject* _GraphicObject;

	void Setdisplayenabled(bool newvalue) { displayenabled = newvalue; }
	void Setphysicsenabled(bool newvalue) { physicsenabled = newvalue; }
	bool Getdisplayenabled() { return displayenabled; }
	bool Getphysicsenabled() { return  physicsenabled; }

	std::string GetName() { return _name; }
	void SetName(std::string name) { _name = name; }
};

#endif

