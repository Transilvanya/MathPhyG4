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
	static void SolveImpulsion(std::list<RigidBodyContact> Contacts)
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


			++it;
		}

	}

	static void SolvePenetration(std::list<RigidBodyContact> Contacts)
	{

		//std::cout << "contact start ________________ \n\n";

		std::list<RigidBodyContact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{
			
			Vector3D r0 = it->RBAnchorPoint[0] - it->rigidbodies[0]->getPosition();
			Vector3D r1 = it->RBAnchorPoint[1] - it->rigidbodies[1]->getPosition();

			Vector3D contactspeed0 = it->rigidbodies[0]->getVitesse() + it->rigidbodies[0]->getRotation() * r0;
			Vector3D contactspeed1 = it->rigidbodies[1]->getVitesse() + it->rigidbodies[1]->getRotation() * r1;

			Vector3D speeddif = contactspeed0 - contactspeed1;

			float k =
				( (it->restitution + 1) * (speeddif & it->contactNormal ) ) /
				( (
					it->contactNormal * (it->rigidbodies[0]->getInverseMasse() + it->rigidbodies[1]->getInverseMasse()) +
					(	it->rigidbodies[0]->GetInverseTenseur() * (r0 * it->contactNormal)  ) * r0 +
					(it->rigidbodies[1]->GetInverseTenseur() * (r1 * it->contactNormal)) * r1
					
					) & it->contactNormal);


			Vector3D newvitesse0 = it->rigidbodies[0]->getVitesse() - it->contactNormal * k * it->rigidbodies[0]->getInverseMasse();
			Vector3D newrotation0 = it->rigidbodies[0]->getRotation() - it->rigidbodies[0]->GetInverseTenseur() * (r0 * (it->contactNormal*k)) ;

			Vector3D newvitesse1 = it->rigidbodies[1]->getVitesse() + it->contactNormal * k * it->rigidbodies[1]->getInverseMasse();
			Vector3D newrotation1 = it->rigidbodies[1]->getRotation() + it->rigidbodies[1]->GetInverseTenseur() * (r1 * (it->contactNormal * k));

			it->rigidbodies[0]->setVitesse(newvitesse0);
			it->rigidbodies[0]->setRotation(newrotation0);

			it->rigidbodies[1]->setVitesse(newvitesse1);
			it->rigidbodies[1]->setRotation(newrotation1);
			++it;
		}

	}

};


#endif
