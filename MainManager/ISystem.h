
#ifndef ISYSTEM_CLASS_H
#define ISYSTEM_CLASS_H


#include <string>

class ISystem
{
public:
	virtual std::string getName() { return "Default"; };
	virtual void Tick() = 0;

};

#endif

