#ifndef CONTACTSOLVERRIGID_CLASS_H
#define CONTACTSOLVERRIGID_CLASS_H


#include "../RigidBody/RigidBody.h"
#include "RigidBodyContact.h"

#include <list>
#include <iostream>
#include <map>


class ContactSolverRigid
{
public:
	float ContactPrecision = 0.001;

	//fill Contacts for the Particules
	virtual void SolveImpulsion(std::list<RigidBodyContact> Contacts)
	{

		//std::cout << "contact start ________________ \n\n";

		std::list<RigidBodyContact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{


			float weight0 = it->rigidbodies[0]->getMasse() / (it->rigidbodies[0]->getMasse() + it->rigidbodies[1]->getMasse());
			float weight1 = it->rigidbodies[1]->getMasse() / (it->rigidbodies[0]->getMasse() + it->rigidbodies[1]->getMasse());

			Vector3D temp0 = it->contactNormal *  weight0 * it->penetration;
			Vector3D temp1 = it->contactNormal * -weight1 * it->penetration;

			it->rigidbodies[0]->setPosition(it->rigidbodies[0]->getPosition() + temp0);
			it->rigidbodies[1]->setPosition(it->rigidbodies[1]->getPosition() + temp1);

			/* --------------------------------------- */

			Vector3D speeddif = (it->rigidbodies[0]->getVitesse() - it->rigidbodies[1]->getVitesse());


			float k = (it->restitution + 1) * (speeddif & it->contactNormal) / (it->rigidbodies[0]->getInverseMasse() + it->rigidbodies[1]->getInverseMasse());


			it->rigidbodies[0]->setVitesse(it->rigidbodies[0]->getVitesse() - it->contactNormal * (k * it->rigidbodies[0]->getInverseMasse()));
			it->rigidbodies[1]->setVitesse(it->rigidbodies[1]->getVitesse() + it->contactNormal * (k * it->rigidbodies[1]->getInverseMasse()));

			++it;
		}

	}

	virtual void SolvePenetration(std::list<RigidBodyContact> Contacts)
	{

		//std::cout << "contact start ________________ \n\n";

		std::list<RigidBodyContact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{


			++it;
		}

	}

};


#endif
