#ifndef TIMESYSTEM_CLASS_H
#define TIMESYSTEM_CLASS_H

#include "ISystem.h"
#include <iostream>
#include <chrono>

class TimeSystem : public ISystem
{
private:
	std::string name = "timesystem";
	int ID = -1;
public:

	TimeSystem()
	{
		StartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		PreviousTime = StartTime;
		NewTime = StartTime;
	}

	int GetName() 
	{
		if (ID == -1)
		{
			int factor = 1;
			int total = 0;
			for (int i = 0; i < name.length(); i++)
			{
				total += factor * name[i];
				factor *= 10;
			}
			ID = total;
		}

		return ID; 
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

