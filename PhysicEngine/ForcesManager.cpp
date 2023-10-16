#include "ForcesManager.h"

ForcesManager::ForcesManager() {
	//init list of particules
	particulesList = std::list<Particules*>();
}		

ForcesManager::~ForcesManager() {

}

void ForcesManager::forcesLoop(int newDeltaT)
{
	this->deltaT = ((float)newDeltaT)/1000;
	//gernerate forces on particules


	//for each particules in particulelist
	for (std::list<Particules*>::iterator it = particulesList.begin(); it != particulesList.end(); ++it)
	{
		//apply forces
		applyForces(*it);
	}

	//Detect collision


}

void ForcesManager::addParticule(Particules* particule)
{
	particulesList.push_back(particule);
}

void ForcesManager::removeParticule(Particules* particule)
{
	particulesList.remove(particule);
}

Particules* ForcesManager::getParticule(int index)
{
	std::list<Particules*>::iterator it = particulesList.begin();
	std::advance(it, index);
	return *it;
}

void ForcesManager::applyForces(Particules* particule)
{
	particule->setForce(particule->getForce() + particule->getAcceleration() * particule->getMasse());
	particule->integrade(this->deltaT);
	particule->setForce(particule->getForce() * 0.0f);
}

