
#ifndef FORCEREGISTRY_CLASS_H
#define FORCEREGISTRY_CLASS_H


#include "../vector/Vector3D.h"
#include "../Particules/Particule.h"
#include "IForce.h"
#include "ForceGravity.h"
#include "ForceDrag.h"
#include "ForceSpring.h"
#include "ForceSpringFixed.h"
#include "ForceBuoyancy.h"
#include "SimpleForce.h"

#include <map>
#include <list>
#include <iostream>


class ForceRegistry
{
private:

	struct ParticuleEntry
	{
		Particule* particule;
		std::map<std::string, IForce*> forces;
	};

	std::map<std::string, ParticuleEntry> ParticuleEntries;

public:
	~ForceRegistry();


	/* for every particule in the registry, apply the sum of all the forces */
	void ApplyForces();

	//add and remove a particule from the 
	void AddParticule(Particule* object);
	void RemoveParticule(std::string name);
	
	void AddForceToParticule(Particule* object, IForce* force, std::string name);
	void RemoveForceFromParticule(std::string nameObject, std::string nameForce);

	IForce* GetForce(std::string nameObject, std::string nameForce);

	std::list<std::string> GetForcesOfParticule(std::string name);



	void AddForceGravityToParticule(Particule* particule, std::string forcename);

	void AddForceSimpleToParticule(Vector3D forcevector,Particule* particule, std::string forcename);

	void AddForceDragToParticule(float k1, float k2, Particule* particule, std::string forcename);

	void AddForceBuoyancyToParticule(float liquidheight, float liquiddensity, Particule* particule, std::string forcename);

	
	void AddForceSpringFixedToParticule(Vector3D anchor, float k, float l0, float maxlength, bool bungeespring, Particule* particule, std::string forcename);

	void AddForceSpringToParticule(float k, float l0, float maxlength, bool bungeespring, Particule* particule1, Particule* particule2, std::string forcename);


	
};


#endif