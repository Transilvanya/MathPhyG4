#ifndef CONTACTSOLVERRIGID_CLASS_H
#define CONTACTSOLVERRIGID_CLASS_H


#include "../RigidBody/RigidBody.h"
#include "./Contacts/Contact.h"

#include <list>
#include <iostream>
#include <map>


class ContactSolverRigid
{
public:
	float ContactPrecision = 0.001;

	//fill Contacts for the Particules
	static void SolvePenetration(std::vector<Contact> Contacts)
	{
		if (Contacts.size() > 0)
			std::cout << "contact start ________________ \n";

		std::vector<Contact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{


			

			float linearInertia0 = it->rigidbodies.first->getMasse();
			float linearInertia1 = it->rigidbodies.second->getMasse();


			Vector3D contactpoint0 = it->contactPoint - it->rigidbodies.first->getPosition();
			Vector3D contactpoint1 = it->contactPoint - it->rigidbodies.second->getPosition();


			Vector3D angularInertiaWorld = contactpoint0 * (it->contactNormal);
			angularInertiaWorld = it->rigidbodies.first->GetInverseTenseur() * angularInertiaWorld;
			angularInertiaWorld = angularInertiaWorld * contactpoint0;
			float angularInertia0 = angularInertiaWorld & it->contactNormal;


			Vector3D angularInertiaWorld1 = contactpoint1 * (it->contactNormal);
			angularInertiaWorld1 = it->rigidbodies.second->GetInverseTenseur() * angularInertiaWorld1;
			angularInertiaWorld1 = angularInertiaWorld1 * contactpoint0;
			float angularInertia1 = angularInertiaWorld1 & it->contactNormal;

			// Keep track of the total inertia from all components.
			float totalInertia = linearInertia0 + linearInertia1 + angularInertia0 + angularInertia1;


			float inverseInertia = 1 / totalInertia;
			float linearWeigth0 = inverseInertia * it->penetration * linearInertia0;
			float linearWeigth1 = inverseInertia * (- it->penetration) * linearInertia1;
			float angularWeigth0 = inverseInertia * it->penetration * angularInertia0;
			float angularWeigth1 = inverseInertia  * (- it->penetration)* angularInertia1;
			



			Vector3D temp0 = it->contactNormal * linearWeigth0;
			Vector3D temp1 = it->contactNormal * linearWeigth1;

			//std::cout << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
			//std::cout << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";

			it->rigidbodies.first->setPosition(it->rigidbodies.second->getPosition() + temp0);
			it->rigidbodies.first->setPosition(it->rigidbodies.second->getPosition() + temp1);

			++it;
		}

	}

	static void SolveImpulsion(std::vector<Contact> Contacts)
	{
		if(Contacts.size() > 0)
			std::cout << "contact start ________________ \n";

		std::vector<Contact>::iterator it = Contacts.begin();
		while (it != Contacts.end())
		{
			std::cout << it->rigidbodies.first->getObjectName() << " " << it->rigidbodies.second->getObjectName() << "\n";


			Vector3D r0 = it->contactPoint - it->rigidbodies.first->getPosition();
			Vector3D r1 = it->contactPoint - it->rigidbodies.second->getPosition();

			Vector3D contactspeed0 = it->rigidbodies.first->getVitesse() + it->rigidbodies.first->getRotation() * r0;
			Vector3D contactspeed1 = it->rigidbodies.second->getVitesse() + it->rigidbodies.second->getRotation() * r1;

			Vector3D speeddif = contactspeed0 - contactspeed1;

			float k =
				( (it->restitution + 1) * (speeddif & it->contactNormal ) ) /
				( (
					it->contactNormal * (it->rigidbodies.first->getInverseMasse() + it->rigidbodies.second->getInverseMasse()) +
					(	it->rigidbodies.first->GetInverseTenseur() * (r0 * it->contactNormal)  ) * r0 +
					(it->rigidbodies.second->GetInverseTenseur() * (r1 * it->contactNormal)) * r1
					
					) & it->contactNormal);


			Vector3D newvitesse0 = it->rigidbodies.first->getVitesse() - it->contactNormal * k * it->rigidbodies.first->getInverseMasse();
			Vector3D newrotation0 = it->rigidbodies.first->getRotation() - it->rigidbodies.first->GetInverseTenseur() * (r0 * (it->contactNormal*k)) ;

			Vector3D newvitesse1 = it->rigidbodies.second->getVitesse() + it->contactNormal * k * it->rigidbodies.second->getInverseMasse();
			Vector3D newrotation1 = it->rigidbodies.second->getRotation() + it->rigidbodies.second->GetInverseTenseur() * (r1 * (it->contactNormal * k));

			/*
			
			std::cout << "" << (it->contactNormal * k).getX() << " " << (it->contactNormal * k).getY() << " " << (it->contactNormal * k).getZ() << "\n";
			
			std::cout << r1.getX() << " " << r1.getY() << " " << r1.getZ() << "\n";

			std::cout << "" << (r1 * (it->contactNormal * k)).getX() << " " << (r1 * (it->contactNormal * k)).getY() << " " << (r1 * (it->contactNormal * k)).getZ() << "\n";
			

			std::cout << "\n";

			std::cout << newvitesse0.getX() << " " << newvitesse0.getY() << " " << newvitesse0.getZ() << "\n";
			std::cout << newrotation0.getX() << " " << newrotation0.getY() << " " << newrotation0.getZ() << "\n";

			std::cout << newvitesse1.getX() << " " << newvitesse1.getY() << " " << newvitesse1.getZ() << "\n";
			std::cout << newrotation1.getX() << " " << newrotation1.getY() << " " << newrotation1.getZ() << "\n";

			*/

			it->rigidbodies.first->setVitesse(newvitesse0);
			it->rigidbodies.first->setRotation(newrotation0);

			it->rigidbodies.second->setVitesse(newvitesse1);
			it->rigidbodies.second->setRotation(newrotation1);
			++it;
		}

	}

};


#endif
