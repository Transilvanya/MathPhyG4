
#ifndef PHYSICENGINE_CLASS_H
#define PHYSICENGINE_CLASS_H
#include <map>
#include <string>
#include "Particules/Particule.h"
#include <iostream>
#include "Forces/ForceRegistry.h"
#include "Contact/ContactRegistry.h"
#include "Contact/LinkRegistry.h"
/*

Vecteur null, => si vecteur nul pas drag => pas de vecteur unitaire


contact how to determine restitution


detection if particule au repos, -> avec norme?

link creer une anchor qui fixe a point
add option for link to break


ajouter centre de masse a objet rigide
object rotation, autour de l'origine de l'objet, autour d'un point

calculer les forces et verifier qu'elles correspondent

resoudre oscillation


trigger?


detecte collision,
creer contact -> type entity...,


solve contact,	si rapide ? passe au travers
				si au repos ? oscille au sol, coller a object et passé en dormant, si en pente?

contact, tige, cable (fixe, 2 bgt), interpénétration, au repos

avec objet sans phy


buoyancy is abosulte and does not check if object is contatined, only vertical coordinates
it should be attached to an object that knows with object it contains to apply and remove the force
when nescessary

*/
class PhysicEngine
{
public:
	static PhysicEngine* _physicengineptr ; 

	static PhysicEngine* GetInstance()
	{
		if (_physicengineptr == nullptr)
		{
			_physicengineptr = new PhysicEngine();
		}

		return _physicengineptr;
	}

	~PhysicEngine();

	void Delete() ;

	void Integrade(float DT);

	void Init() {};

	// --------------------------------------------------------------------------------
	void CreateParticule(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, float masse, std::string name);
	Particule* GetParticule(std::string name);

	// --------------------------------------------------------------------------------
	/*
	void CreateSphereObject(Vector3D newPosition, Vector3D newVitesse, Vector3D newAcceleration, std::string _name, float _Radius)
	{
		SphereObject* SO = new SphereObject(newPosition, newVitesse, newAcceleration, _name, _Radius);
		_physicobjects.emplace(_name, SO);
		_forceregistry.AddPhyObject(SO);
		ElementToIntegrade.emplace(_name, SO);

	}
	
	SphereObject* GetSphereObject(std::string name)
	{

		if (_physicobjects.count(name) && _physicobjects.find(name)->second->getType() == 1)
			return (SphereObject*)_physicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get Sphere " << name << "\n";
			return nullptr;
		}

	}
	*/

	// --------------------------------------------------------------------------------
	void RemoveParticule(std::string name);
	// --------------------------------------------------------------------------------

	ForceRegistry* GetForceRegistry();
	
	LinkRegistry* GetLinkRegistry() { return &_linkregistry; }
private:

	std::map<std::string, Particule*> _physicobjects;

	ContactRegistry _contactregistry;
	ForceRegistry _forceregistry;
	LinkRegistry _linkregistry;
};

#endif

