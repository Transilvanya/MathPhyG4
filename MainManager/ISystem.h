
#ifndef ISYSTEM_CLASS_H
#define ISYSTEM_CLASS_H


#include <string>

class ISystem
{
public:
	virtual int GetName() = 0;
	virtual void Tick() = 0;

};

#endif

