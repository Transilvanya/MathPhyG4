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

			if (it->penetration > 0.001)
			{

				float linearInertia0 = it->rigidbodies.first->getMasse();
				float linearInertia1 = it->rigidbodies.second->getMasse();


				Vector3D contactpoint0 = it->contactPoint - it->rigidbodies.first->getPosition();
				Vector3D contactpoint1 = it->contactPoint - it->rigidbodies.second->getPosition();


				//	std::cout << "Pos 0 : " << it->rigidbodies.first->getPosition().getX() << " " << it->rigidbodies.first->getPosition().getY() << " " << it->rigidbodies.first->getPosition().getZ() << "\n";
				//	std::cout << "Pos 1 : " << it->rigidbodies.second->getPosition().getX() << " " << it->rigidbodies.second->getPosition().getY() << " " << it->rigidbodies.second->getPosition().getZ() << "\n";
				//	std::cout << "contact point : " << contactpoint0.getX() << " " << contactpoint0.getY() << " " << contactpoint0.getZ() << "\n";


				Vector3D angularInertiaWorld = contactpoint0 * (it->contactNormal);
				//std::cout << "contact point * contact normal " << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";

				Matrice33 tempmat = it->rigidbodies.first->GetInverseTenseur();

				//std::cout << "InverseTenseur\n";
				//std::cout << tempmat.getValues(0) << " " << tempmat.getValues(1) << " " << tempmat.getValues(2) << "\n";
				//std::cout << tempmat.getValues(3) << " " << tempmat.getValues(4) << " " << tempmat.getValues(5) << "\n";
				//std::cout << tempmat.getValues(6) << " " << tempmat.getValues(7) << " " << tempmat.getValues(8) << "\n\n";

				angularInertiaWorld = tempmat * angularInertiaWorld;
				//std::cout << "Inverse tensuer * inertia " << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";

				angularInertiaWorld = angularInertiaWorld * contactpoint0;
				//std::cout << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";

				float angularInertia0 = angularInertiaWorld & it->contactNormal;


				Vector3D angularInertiaWorld1 = contactpoint1 * (it->contactNormal);
				angularInertiaWorld1 = it->rigidbodies.second->GetInverseTenseur() * angularInertiaWorld1;
				angularInertiaWorld1 = angularInertiaWorld1 * contactpoint0;
				float angularInertia1 = angularInertiaWorld1 & it->contactNormal;


				//std::cout << linearInertia0 << " " << linearInertia1 << " " << angularInertia0 << " " << angularInertia1 << "\n";

				if (it->rigidbodies.first->getIsStatic())
				{
					linearInertia0 = 0;
					angularInertia0 = 0;
				}

				if (it->rigidbodies.second->getIsStatic())
				{
					linearInertia1 = 0;
					angularInertia1 = 0;
				}
				// Keep track of the total inertia from all components.
				float totalInertia = linearInertia0 + linearInertia1 + angularInertia0 + angularInertia1;


				float inverseInertia = 1 / totalInertia;

				//std::cout << "total init : " << totalInertia << "inv " << inverseInertia << "\n";
				//std::cout << it->penetration << "\n";

				float linearWeigth0 = inverseInertia * it->penetration * linearInertia0;
				float linearWeigth1 = inverseInertia * (-it->penetration) * linearInertia1;
				float angularWeigth0 = inverseInertia * it->penetration * angularInertia0;
				float angularWeigth1 = inverseInertia * (-it->penetration) * angularInertia1;




				Vector3D temp0 = it->contactNormal * linearWeigth0;
				Vector3D temp1 = it->contactNormal * linearWeigth1;
				/*
				std::cout << "\n";
				std::cout << it->penetration << "\n";
				std::cout << "temp 0 : " << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
				std::cout << "temp 1 : " << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";
*/
				it->rigidbodies.first->setPosition(it->rigidbodies.first->getPosition() + temp0);
				it->rigidbodies.second->setPosition(it->rigidbodies.second->getPosition() + temp1);




				// -----------------------------------------------------------------
				//
				//
				//
				// -----------------------------------------------------------------

				Vector3D impulsiveTorque0 = contactpoint0 * it->contactNormal;
				Vector3D impulsePerMove0 = it->rigidbodies.first->GetInverseTenseur() * impulsiveTorque0;
				Vector3D rotPerMove0 = impulsePerMove0 * (1 / angularInertia0);
				if (angularInertia0 == 0)
					rotPerMove0 = Vector3D(0, 0, 0);

				Vector3D rotation0 = rotPerMove0 * angularWeigth0;

				//	std::cout << rotation0.getX() << " " << rotation0.getY() << " " << rotation0.getZ() << "\n";
				Quaternion quat = it->rigidbodies.first->getOrientation();
				quat.RotateByVector(rotation0);
				//	std::cout << quat.getW() << " " << quat.getX() << " " << quat.getY() << " " << quat.getZ() << "\n";

				if (rotation0.getNorm() > 0.00001)
				{
					Quaternion quat0 = it->rigidbodies.first->getOrientation();
					quat0.RotateByVector(rotation0);
					it->rigidbodies.first->setOrientation(quat0);
				}/*
				else
				{
					//debug
					Quaternion quat0 = it->rigidbodies.first->getOrientation();
					quat0.RotateByVector(Vector3D(0,0,0.01f));
					it->rigidbodies.first->setOrientation(quat0);
				}*/


				Vector3D impulsiveTorque1 = contactpoint1 * it->contactNormal;
				Vector3D impulsePerMove1 = it->rigidbodies.second->GetInverseTenseur() * impulsiveTorque0;
				Vector3D rotPerMove1 = impulsePerMove1 * (1 / angularInertia1);
				if (angularInertia1 != 0)
					rotPerMove1 = Vector3D(0, 0, 0);

				Vector3D rotation1 = rotPerMove1 * angularWeigth1;
				if (rotation1.getNorm() > 0.001)
				{
					Quaternion quat1 = it->rigidbodies.second->getOrientation();
					std::cout << quat1.getW() << " " << quat1.getX() << " " << quat1.getY() << " " << quat1.getZ() << "\n";
					quat1.RotateByVector(rotation1);
					std::cout << quat1.getW() << " " << quat1.getX() << " " << quat1.getY() << " " << quat1.getZ() << "\n";
					it->rigidbodies.second->setOrientation(quat1);
				}

			}
		
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

			float m0 = (it->rigidbodies.first->getIsStatic() ? 0 : it->rigidbodies.first->getInverseMasse());
			float m1 = (it->rigidbodies.second->getIsStatic() ? 0 : it->rigidbodies.second->getInverseMasse());

			Vector3D d0 = (it->rigidbodies.first->getIsStatic() ? Vector3D(0,0,0) : (it->rigidbodies.first->GetInverseTenseur() * (r0 * it->contactNormal)) * r0 );
			Vector3D d1 = (it->rigidbodies.second->getIsStatic() ? Vector3D(0, 0, 0) : (it->rigidbodies.second->GetInverseTenseur() * (r1 * it->contactNormal)) * r1);

			float k =
				( (it->restitution + 1) * (speeddif & it->contactNormal ) ) /
				( (
					(it->contactNormal * (m0 + m1 ) ) +	d0 + d1
					) & it->contactNormal);


			Vector3D newvitesse0 = it->rigidbodies.first->getVitesse() - it->contactNormal * k * m0;
			//Vector3D newrotation0 = it->rigidbodies.first->getRotation() - it->rigidbodies.first->GetInverseTenseur() * (r0 * (it->contactNormal*k)) ;

			Vector3D newvitesse1 = it->rigidbodies.second->getVitesse() + it->contactNormal * k * it->rigidbodies.second->getInverseMasse();
			//Vector3D newrotation1 = it->rigidbodies.second->getRotation() + it->rigidbodies.second->GetInverseTenseur() * (r1 * (it->contactNormal * k));

			if (it->rigidbodies.first->getIsStatic())
			{
				newvitesse0 = Vector3D(0, 0, 0);
				//newrotation0 = Vector3D(0, 0, 0);
			}
			if (it->rigidbodies.second->getIsStatic())
			{
				newvitesse1 = Vector3D(0, 0, 0);
				//newrotation1 = Vector3D(0, 0, 0);
			}
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
		//	it->rigidbodies.first->setRotation(newrotation0);

			it->rigidbodies.second->setVitesse(newvitesse1);
		//	it->rigidbodies.second->setRotation(newrotation1);
			++it;
		}

	}

};


#endif
