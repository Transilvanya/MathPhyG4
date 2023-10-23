
#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "../PhysicEngine/Particules/Particule.h"
#include "../GraphicEngine/GraphicObject.h"
#include <string>

class Entity
{
private:
	std::string _name = "default";


public:

	Entity(Particule* PO, GraphicObject* GO, std::string name)
	{
		_name = name;
		_PhysicObject = PO;
		_GraphicObject = GO;
	}

	Particule* _PhysicObject = nullptr;
	GraphicObject* _GraphicObject = nullptr;

	std::string getName() { return _name; }
	void SetName(std::string name) { _name = name; }

};

#endif

