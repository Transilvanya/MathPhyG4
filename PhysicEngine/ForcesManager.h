#pragma once
#ifndef MATHPHYG4_FORCESMANAGER_H
#define MATHPHYG4_FORCESMANAGER_H

#include "../Particules/Particules.h"
#include <list>
#include "../MainManager/TimeSystem.h"
#include "../MainManager/MainManager.h"

class ForcesManager
{
	public:
		ForcesManager();
		~ForcesManager();
		void forcesLoop(int newDeltaT);
		void addParticule(Particules* particule);
		void removeParticule(Particules* particule);
		Particules* getParticule(int index);
		void applyForces(Particules* particule);

	private:
		//list of particules
		std::list<Particules*> particulesList;
		float deltaT;

		
};

#endif //MATHPHYG4_FORCESMANAGER_H