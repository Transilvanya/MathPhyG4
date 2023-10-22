#ifndef TIMESYSTEM_CLASS_H
#define TIMESYSTEM_CLASS_H

#include "ISystem.h"
#include <iostream>
#include <chrono>

class TimeSystem : public ISystem
{
private:

public:

	TimeSystem()
	{
		StartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		PreviousTime = StartTime;
		NewTime = StartTime;
	}

	std::string getName() 
	{

		return "TimeSystem";
	}

	virtual void Tick()
	{ 
		//std::cout << "time system " << GetDeltaT() << " "<< NewTime << " \n";
		PreviousTime = NewTime;
		NewTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	int GetTime()
	{
		return NewTime - StartTime;
	}

	int GetDeltaT()
	{
		return NewTime - PreviousTime;
	}
private:
	
	__int64 StartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	__int64 PreviousTime = StartTime;
	__int64 NewTime = StartTime;
};

#endif

