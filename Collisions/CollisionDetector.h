#pragma once
#include "../PhysicEngine/Particules/Particule.h"
#include "../Contact/ParticleContact.h"
#include "../PhysicEngine/PhysicEngine.h"

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	void isColliding(Particule part1, Particule part2);

private:
	//list of contact
	std::list<ParticleContact> contacts;

};
