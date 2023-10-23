#pragma once
#ifndef MATHPHYG4_COLLISIONDETECOR_H
#define MATHPHYG4_COLLISIONDETECOR_H
#include "../PhysicEngine/Particules/Particule.h"
#include "../Contact/ParticleContact.h"
#include <list>
#include <map>

class CollisionDetector
{
public:
	void collisionDetectorApplication(std::map<std::string, Particule*> _physicobjects);
	void isColliding(Particule part1, Particule part2);

	std::list<ParticleContact> getContacts() { return contacts; }

private:
	//list of contact
	std::list<ParticleContact> contacts;

};

#endif // MATHPHYG4_COLLISIONDETECOR_H
