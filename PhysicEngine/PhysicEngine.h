
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <list>
#include "PhysicObject.h"

class PhysicEngine
{
public:
	static PhysicEngine* _physicengineptr;

	static PhysicEngine* GetInstance()
	{
		if (_physicengineptr == nullptr)
		{
			_physicengineptr = new PhysicEngine();
		}

		return _physicengineptr;
	}

	void AddElementToIntegrade(PhysicObject* object)
	{
		ElementToIntegrade.push_back(object);
	}

private:

	std::list<PhysicObject*> ElementToIntegrade;
};

#endif

