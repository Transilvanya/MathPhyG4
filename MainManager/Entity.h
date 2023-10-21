
#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "../PhysicEngine/Particules/Particule.h"
#include "../GraphicEngine/GraphicObject.h"
#include <string>

class Entity
{
private:
	std::string _name = "default";

	bool DisplayEnabled = true;
	bool PhysicEnabled = true;

public:

	Entity(Particule* PO, GraphicObject* GO, std::string name)
	{
		_name = name;
		_PhysicObject = PO;
		_GraphicObject = GO;
	}

	Particule* _PhysicObject = nullptr;
	GraphicObject* _GraphicObject = nullptr;



	void Setdisplayenabled(bool newvalue) { DisplayEnabled = newvalue; }
	void Setphysicsenabled(bool newvalue) { PhysicEnabled=newvalue; }
	bool Getdisplayenabled() { return DisplayEnabled; }
	bool Getphysicsenabled() { return PhysicEnabled; }

	std::string getName() { return _name; }
	void SetName(std::string name) { _name = name; }

};

#endif

