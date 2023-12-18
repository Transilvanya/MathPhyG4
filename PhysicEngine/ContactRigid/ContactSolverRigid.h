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


	static bool enableDisplay() {
		return false;
	}
	
	static bool enableDisplay2() {
		return false;
	}

	static bool enableDisplay3() {
		return false;
	}


	static bool enablePenRot() {
		return true;
	}

	//fill Contacts for the Particules
	static void SolvePenetration(Contact Contacts)
	{
		std::cout << "Solve Pen\n";
		if (Contacts.penetration > 0.001)
		{

			if (enableDisplay())
			{
				std::cout << "\n";


				std::cout << Contacts.rigidbodies.first->getObjectName() << "\n";
				std::cout << Contacts.rigidbodies.second->getObjectName() << "\n";
			}
			float linearInertia0 = Contacts.rigidbodies.first->getInverseMasse();
			float linearInertia1 = Contacts.rigidbodies.second->getInverseMasse();
			if (enableDisplay())
			{
				std::cout << "Linearinertia\t" << linearInertia0 << "\t" << linearInertia1 << "\n";
			}
			Vector3D contactpoint0 = Contacts.contactPoint - Contacts.rigidbodies.first->getPosition();
			Vector3D contactpoint1 = Contacts.contactPoint - Contacts.rigidbodies.second->getPosition();
			if (enableDisplay2())
			{
				std::cout << "contactPoint : " << Contacts.contactPoint.getX() << " " << Contacts.contactPoint.getY() << " " << Contacts.contactPoint.getZ() << "\n";
				std::cout << "Pos 0 : " << Contacts.rigidbodies.first->getPosition().getX() << " " << Contacts.rigidbodies.first->getPosition().getY() << " " << Contacts.rigidbodies.first->getPosition().getZ() << "\n";
				std::cout << "Pos 1 : " << Contacts.rigidbodies.second->getPosition().getX() << " " << Contacts.rigidbodies.second->getPosition().getY() << " " << Contacts.rigidbodies.second->getPosition().getZ() << "\n";
				std::cout << "contactpointRelativePos0 : " << contactpoint0.getX() << " " << contactpoint0.getY() << " " << contactpoint0.getZ() << "\n";
				std::cout << "contactpointRelativePos1 : " << contactpoint1.getX() << " " << contactpoint1.getY() << " " << contactpoint1.getZ() << "\n";
				std::cout << "contactNormal : " << Contacts.contactNormal.getX() << " " << Contacts.contactNormal.getY() << " " << Contacts.contactNormal.getZ() << "\n";

				std::cout << "\n";

			}
			//________________ _________________________________ angular inertia



			Vector3D angularInertiaWorld = contactpoint0 * (Contacts.contactNormal);
			if (enableDisplay())
			{
				std::cout << "\tcontactpoint0 * contact normal " << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";
			}
			Matrice33 tempmat = Contacts.rigidbodies.first->GetInverseTenseur();
			//std::cout << "InverseTenseur\n";
			//std::cout << tempmat.getValues(0) << " " << tempmat.getValues(1) << " " << tempmat.getValues(2) << "\n";
			//std::cout << tempmat.getValues(3) << " " << tempmat.getValues(4) << " " << tempmat.getValues(5) << "\n";
			//std::cout << tempmat.getValues(6) << " " << tempmat.getValues(7) << " " << tempmat.getValues(8) << "\n\n";
			angularInertiaWorld = tempmat * angularInertiaWorld;
			if (enableDisplay())
			{
				std::cout << "\tInverse tensuer * inertia " << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";
			}
			angularInertiaWorld = angularInertiaWorld * contactpoint0;
			if (enableDisplay())
			{
				std::cout << "\tangularInertiaWorld\t" << angularInertiaWorld.getX() << " " << angularInertiaWorld.getY() << " " << angularInertiaWorld.getZ() << "\n";
			}
			float angularInertia0 = angularInertiaWorld & Contacts.contactNormal;

			if (Contacts.rigidbodies.first->getIsStatic())
				angularInertia0 = 0;
			if (enableDisplay())
			{
				std::cout << "\tangularInertia0 " << angularInertia0 << "\n";
				std::cout << "\n";
			}


			//________________ _________________________________ angular inertia



			Vector3D angularInertiaWorld1 = contactpoint1 * (Contacts.contactNormal);
			if (enableDisplay())
			{
				std::cout << "\tcontactpoint1 * contact normal " << angularInertiaWorld1.getX() << " " << angularInertiaWorld1.getY() << " " << angularInertiaWorld1.getZ() << "\n";
			}
			angularInertiaWorld1 = Contacts.rigidbodies.second->GetInverseTenseur() * angularInertiaWorld1;
			if (enableDisplay())
			{
				std::cout << "\tInverse tensuer * inertia " << angularInertiaWorld1.getX() << " " << angularInertiaWorld1.getY() << " " << angularInertiaWorld1.getZ() << "\n";
			}
			angularInertiaWorld1 = angularInertiaWorld1 * contactpoint0;
			if (enableDisplay())
			{
				std::cout << "\tangularInertiaWorld1\t" << angularInertiaWorld1.getX() << " " << angularInertiaWorld1.getY() << " " << angularInertiaWorld1.getZ() << "\n";
			}
			float angularInertia1 = angularInertiaWorld1 & Contacts.contactNormal;

			if (Contacts.rigidbodies.second->getIsStatic())
				angularInertia1 = 0;

			if (enableDisplay())
			{
				std::cout << "\tangularInertia1 " << angularInertia1 << "\n";
				std::cout << "\n";
			}
			//________________ _________________________________ angular inertia


			//std::cout << "ANUGLAR INERTIA DISABLED\n";
		
				//	angularInertia0 = 0;
				//	angularInertia1 = 0;
				
				if (Contacts.rigidbodies.first->getIsStatic())
				{
					linearInertia0 = 0;
					angularInertia0 = 0;
				}

				if (Contacts.rigidbodies.second->getIsStatic())
				{
					linearInertia1 = 0;
					angularInertia1 = 0;
				}

				// Keep track of the total inertia from all components.
				float totalInertia = linearInertia0 + linearInertia1 + angularInertia0 + angularInertia1;
				float inverseInertia = 1 / totalInertia;

				//std::cout << "total init : " << totalInertia << "inv " << inverseInertia << "\n";
				//std::cout << Contacts.penetration << "\n";

				float linearWeigth0 = inverseInertia * -Contacts.penetration * linearInertia0;
				float linearWeigth1 = inverseInertia * Contacts.penetration * linearInertia1;


				Vector3D temp0 = Contacts.contactNormal * linearWeigth0;
				Vector3D temp1 = Contacts.contactNormal * linearWeigth1;
				if (enableDisplay3())
				{
					std::cout << "penetration : " << Contacts.penetration << "\n";
					std::cout << "temp 0 : " << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
					std::cout << "temp 1 : " << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";

					Vector3D v0 = Contacts.rigidbodies.first->getPosition();
					Vector3D v1 = Contacts.rigidbodies.second->getPosition();
					Quaternion q0 = Contacts.rigidbodies.first->getOrientation();
					Quaternion q1 = Contacts.rigidbodies.second->getOrientation();
					std::cout << "Pos 0 : " << v0.getX() << " " << v0.getY() << " " << v0.getZ() << "\n";
					std::cout << "Pos 1 : " << v1.getX() << " " << v1.getY() << " " << v1.getZ() << "\n";

					std::cout << "Rot 0 : " << q0.getW() << " " << q0.getX() << " " << q0.getY() << " " << q0.getZ() << "\n";
					std::cout << "Rot 1 : " << q1.getW() << " " << q1.getX() << " " << q1.getY() << " " << q1.getZ() << "\n";
				}
				

				//std::cout << "LINEAR PEN DESACTIVATED !\n";
				Contacts.rigidbodies.first->setPosition(Contacts.rigidbodies.first->getPosition() + temp0);
				Contacts.rigidbodies.second->setPosition(Contacts.rigidbodies.second->getPosition() + temp1);

				


				// -----------------------------------------------------------------
				//
				//
				//
				// -----------------------------------------------------------------
				if (enableDisplay())
				{
					std::cout << "\n";
				}
				float angularWeigth0 = inverseInertia * Contacts.penetration * angularInertia0;
				float angularWeigth1 = inverseInertia * -Contacts.penetration * angularInertia1;
				if (enableDisplay())
				{
					std::cout << "\tangularweigth\t" << angularWeigth0 << "\t" << angularWeigth1 << "\n";
				}

				Vector3D impulsiveTorque0 = contactpoint0 * Contacts.contactNormal;
				Vector3D impulsePerMove0 = Contacts.rigidbodies.first->GetInverseTenseur() * impulsiveTorque0;
				Vector3D rotPerMove0 = impulsePerMove0 * (1 / angularInertia0);
				if (angularInertia0 == 0)
					rotPerMove0 = Vector3D(0, 0, 0);

				Vector3D rotation0 = rotPerMove0 * angularWeigth0;

				if (enableDisplay())
				{

					std::cout << "contactpoint0 * Contacts.contactNormal\t" << impulsiveTorque0.getX() << " " << impulsiveTorque0.getY() << " " << impulsiveTorque0.getZ() << "\n";
					std::cout << "Contacts.rigidbodies.first->GetInverseTenseur() * impulsiveTorque0\t" << impulsePerMove0.getX() << " " << impulsePerMove0.getY() << " " << impulsePerMove0.getZ() << "\n";
					std::cout << "impulsePerMove0 * (1 / angularInertia0)\t" << rotPerMove0.getX() << " " << rotPerMove0.getY() << " " << rotPerMove0.getZ() << "\n";
				}
				if (enableDisplay3())
				{
					std::cout << "Rotation0 ( rotPerMove0 * angularWeigth0 )\t" << rotation0.getX() << " " << rotation0.getY() << " " << rotation0.getZ() << "\n";
				}
				Quaternion quat = Contacts.rigidbodies.first->getOrientation();
				if (enableDisplay())
				{
					std::cout << "quat0\t" << quat.getW() << " " << quat.getX() << " " << quat.getY() << " " << quat.getZ() << "\n";
				}
				quat.RotateByVector(rotation0);
				if (enableDisplay())
				{
					std::cout << "quat0'\t" << quat.getW() << " " << quat.getX() << " " << quat.getY() << " " << quat.getZ() << "\n";
					std::cout << "\n";
				}
				//Contacts.rigidbodies.first->setOrientation(quat);

					Quaternion quat0 = Contacts.rigidbodies.first->getOrientation();
							
					//quat0.RotateByVector(Vector3D(0,0,-0.1f));
					
					//
					if(enablePenRot())
						Contacts.rigidbodies.first->setOrientation(quat);				
					else
						std::cout << "PENETRATION ORIENTATTION\n";
					


					// *****************************
					//
					//
					//
					// *****************************




				Vector3D impulsiveTorque1 = contactpoint1 * Contacts.contactNormal;
				Vector3D impulsePerMove1 = Contacts.rigidbodies.second->GetInverseTenseur() * impulsiveTorque1;
				Vector3D rotPerMove1 = impulsePerMove1 * (1 / angularInertia1);
				if (angularInertia1 == 0)
					rotPerMove1 = Vector3D(0, 0, 0);

				if (enableDisplay())
				{

					std::cout << "contactpoint1 * Contacts.contactNormal\t" << impulsiveTorque1.getX() << " " << impulsiveTorque1.getY() << " " << impulsiveTorque1.getZ() << "\n";
					std::cout << "Contacts.rigidbodies.second->GetInverseTenseur() * impulsiveTorque1\t" << impulsePerMove1.getX() << " " << impulsePerMove1.getY() << " " << impulsePerMove1.getZ() << "\n";
					std::cout << "impulsePerMove1 * (1 / angularInertia1)\t" << rotPerMove1.getX() << " " << rotPerMove1.getY() << " " << rotPerMove1.getZ() << "\n";

				}

				Vector3D rotation1 = rotPerMove1 * angularWeigth1;
				if (enableDisplay3())
				{
					std::cout << "Rotation ( rotPerMove1 * angularWeigth1 )\t" << rotation1.getX() << " " << rotation1.getY() << " " << rotation1.getZ() << "\n";
				}
				Quaternion quat1 = Contacts.rigidbodies.second->getOrientation();
				if (enableDisplay())
				{
					std::cout << "quat1 " << quat1.getW() << " " << quat1.getX() << " " << quat1.getY() << " " << quat1.getZ() << "\n";
				}
				quat1.RotateByVector(rotation1);
				if (enableDisplay())
				{
					std::cout << "quat1 ' " << quat1.getW() << " " << quat1.getX() << " " << quat1.getY() << " " << quat1.getZ() << "\n";
				}

				
				//tempquat.RotateByVector(Vector3D(0,0,0.01f));

				if(enablePenRot())
					Contacts.rigidbodies.second->setOrientation(quat1);
				

				if (enableDisplay3())
				{

					Vector3D v0 = Contacts.rigidbodies.first->getPosition();
					Vector3D v1 = Contacts.rigidbodies.second->getPosition();
					Quaternion q0 = Contacts.rigidbodies.first->getOrientation();
					Quaternion q1 = Contacts.rigidbodies.second->getOrientation();
					std::cout << "Pos 0 : " << v0.getX() << " " << v0.getY() << " " << v0.getZ() << "\n";
					std::cout << "Pos 1 : " << v1.getX() << " " << v1.getY() << " " << v1.getZ() << "\n";

					std::cout << "Rot 0 : " << q0.getW() << " " << q0.getX() << " " << q0.getY() << " " << q0.getZ() << "\n";
					std::cout << "Rot 1 : " << q1.getW() << " " << q1.getX() << " " << q1.getY() << " " << q1.getZ() << "\n";
				}

				if (enableDisplay())
				{
					std::cout << "end Conctact _____________ \n";
				}
			}
		
	}

	static void SolveImpulsion(Contact Contacts)
	{
		std::cout << "Solve Imp\n";

		if (enableDisplay())
		{
			std::cout << "\nStart Impulsion\n";
			std::cout << Contacts.rigidbodies.first->getObjectName() << " " << Contacts.rigidbodies.second->getObjectName() << "\n";

			std::cout << "Contacts.rigidbodies.first->getPosition() \t" << Contacts.rigidbodies.first->getPosition().getX() << "\t" << Contacts.rigidbodies.first->getPosition().getY() << "\t" << Contacts.rigidbodies.first->getPosition().getZ() << "\n";
			std::cout << "Contacts.rigidbodies.second->getPosition() \t" << Contacts.rigidbodies.second->getPosition().getX() << "\t" << Contacts.rigidbodies.second->getPosition().getY() << "\t" << Contacts.rigidbodies.second->getPosition().getZ() << "\n";

			std::cout << "Contacts.contactPoint \t" << Contacts.contactPoint.getX() << "\t" << Contacts.contactPoint.getY() << "\t" << Contacts.contactPoint.getZ() << "\n";

			std::cout << "Contacts.contactNormal \t" << Contacts.contactNormal.getX() << "\t" << Contacts.contactNormal.getY() << "\t" << Contacts.contactNormal.getZ() << "\n";

			std::cout << "Contacts.penetration\t" << Contacts.penetration << "\n";
		}
			Vector3D r0 = Contacts.contactPoint - Contacts.rigidbodies.first->getPosition();
			Vector3D r1 = Contacts.contactPoint - Contacts.rigidbodies.second->getPosition();
			if (enableDisplay())
			{
				std::cout << "r0 \t" << r0.getX() << "\t" << r0.getY() << "\t" << r0.getZ() << "\n";
				std::cout << "r1 \t" << r1.getX() << "\t" << r1.getY() << "\t" << r1.getZ() << "\n";

				std::cout << "Contacts.rigidbodies.first->getVitesse() \t" << Contacts.rigidbodies.first->getVitesse().getX() << "\t" << Contacts.rigidbodies.first->getVitesse().getY() << "\t" << Contacts.rigidbodies.first->getVitesse().getZ() << "\n";
				std::cout << "Contacts.rigidbodies.first->getRotation() \t" << Contacts.rigidbodies.first->getRotation().getX() << "\t" << Contacts.rigidbodies.first->getRotation().getY() << "\t" << Contacts.rigidbodies.first->getRotation().getZ() << "\n";
				std::cout << "Contacts.rigidbodies.second->getVitesse() \t" << Contacts.rigidbodies.second->getVitesse().getX() << "\t" << Contacts.rigidbodies.second->getVitesse().getY() << "\t" << Contacts.rigidbodies.second->getVitesse().getZ() << "\n";
				std::cout << "Contacts.rigidbodies.second->getRotation() \t" << Contacts.rigidbodies.second->getRotation().getX() << "\t" << Contacts.rigidbodies.second->getRotation().getY() << "\t" << Contacts.rigidbodies.second->getRotation().getZ() << "\n";
			}
			Vector3D contactspeed0 = (Contacts.rigidbodies.first->getIsStatic() ? Vector3D(0, 0, 0) : Contacts.rigidbodies.first->getVitesse() + Contacts.rigidbodies.first->getRotation() * r0);
			Vector3D contactspeed1 = (Contacts.rigidbodies.second->getIsStatic() ? Vector3D(0, 0, 0) : Contacts.rigidbodies.second->getVitesse() + Contacts.rigidbodies.second->getRotation() * r1);



			if (enableDisplay())
			{
				std::cout << "contactspeed0 \t" << contactspeed0.getX() << "\t" << contactspeed0.getY() << "\t" << contactspeed0.getZ() << "\n";
				std::cout << "contactspeed1 \t" << contactspeed1.getX() << "\t" << contactspeed1.getY() << "\t" << contactspeed1.getZ() << "\n";
			}
			Vector3D speeddif = contactspeed0 - contactspeed1;

			float m0 = (Contacts.rigidbodies.first->getIsStatic() ? 0 : Contacts.rigidbodies.first->getInverseMasse());
			float m1 = (Contacts.rigidbodies.second->getIsStatic() ? 0 : Contacts.rigidbodies.second->getInverseMasse());
			if (enableDisplay())
			{
				std::cout << "m0 \t" << m0 << "\n";
				std::cout << "m1 \t" << m1 << "\n";
			}
			Vector3D d0 = (Contacts.rigidbodies.first->getIsStatic() ? Vector3D(0,0,0) : (Contacts.rigidbodies.first->GetInverseTenseur() * (r0 * Contacts.contactNormal)) * r0 );
			Vector3D d1 = (Contacts.rigidbodies.second->getIsStatic() ? Vector3D(0, 0, 0) : (Contacts.rigidbodies.second->GetInverseTenseur() * (r1 * Contacts.contactNormal)) * r1);
						
			float k =
				( (Contacts.restitution + 1) * (speeddif & Contacts.contactNormal ) ) /
				( (
					(Contacts.contactNormal * (m0 + m1 ) ) +	d0 + d1
					) & Contacts.contactNormal);
			
			if (enableDisplay())
			{
				std::cout << "d0 \t" << d0.getX() << "\t" << d0.getY() << "\t" << d0.getZ() << "\n";
				std::cout << "d1 \t" << d1.getX() << "\t" << d1.getY() << "\t" << d1.getZ() << "\n";
				std::cout << "k \t" << k << "\n";
			}
			


			Vector3D newvitesse0 = Contacts.rigidbodies.first->getVitesse() - Contacts.contactNormal * k * m0;
			Vector3D newrotation0 = Contacts.rigidbodies.first->getRotation() - Contacts.rigidbodies.first->GetInverseTenseur() * (r0 * (Contacts.contactNormal*k)) ;

			Vector3D newvitesse1 = Contacts.rigidbodies.second->getVitesse() + Contacts.contactNormal * k * m1;
			Vector3D newrotation1 = Contacts.rigidbodies.second->getRotation() + Contacts.rigidbodies.second->GetInverseTenseur() * (r1 * (Contacts.contactNormal * k));

			if (Contacts.rigidbodies.first->getIsStatic())
			{
				newvitesse0 = Vector3D(0, 0, 0);
				newrotation0 = Vector3D(0, 0, 0);
			}
			if (Contacts.rigidbodies.second->getIsStatic())
			{
				newvitesse1 = Vector3D(0, 0, 0);
				newrotation1 = Vector3D(0, 0, 0);
			}
			/*
			
			std::cout << "" << (Contacts.contactNormal * k).getX() << " " << (Contacts.contactNormal * k).getY() << " " << (Contacts.contactNormal * k).getZ() << "\n";
			
			std::cout << r1.getX() << " " << r1.getY() << " " << r1.getZ() << "\n";

			std::cout << "" << (r1 * (Contacts.contactNormal * k)).getX() << " " << (r1 * (Contacts.contactNormal * k)).getY() << " " << (r1 * (Contacts.contactNormal * k)).getZ() << "\n";
			

			std::cout << "\n";

			std::cout << newvitesse0.getX() << " " << newvitesse0.getY() << " " << newvitesse0.getZ() << "\n";
			std::cout << newrotation0.getX() << " " << newrotation0.getY() << " " << newrotation0.getZ() << "\n";

			std::cout << newvitesse1.getX() << " " << newvitesse1.getY() << " " << newvitesse1.getZ() << "\n";
			std::cout << newrotation1.getX() << " " << newrotation1.getY() << " " << newrotation1.getZ() << "\n";

			*/

			if (enableDisplay())
			{
				std::cout << "newvitesse0 \t" << newvitesse0.getX() << "\t" << newvitesse0.getY() << "\t" << newvitesse0.getZ() << "\n";
				std::cout << "newvitesse1 \t" << newvitesse1.getX() << "\t" << newvitesse1.getY() << "\t" << newvitesse1.getZ() << "\n";

				std::cout << "newrotation0 \t" << newrotation0.getX() << "\t" << newrotation0.getY() << "\t" << newrotation0.getZ() << "\n";
				std::cout << "newrotation1 \t" << newrotation1.getX() << "\t" << newrotation1.getY() << "\t" << newrotation1.getZ() << "\n";
				std::cout << "\nEnd Impulsion\n";
			}
			Contacts.rigidbodies.first->setVitesse(newvitesse0);
			Contacts.rigidbodies.first->setRotation(newrotation0);

			Contacts.rigidbodies.second->setVitesse(newvitesse1);
			Contacts.rigidbodies.second->setRotation(newrotation1);
		

	}



	static void SolveContacts(std::vector<Contact> contacts)
	{
		

	map<Contact*, int> penetrationcontacts;
	map<Contact*, int> impulsecontacts;


	std::vector<Contact>::iterator itc = contacts.begin();
	while (itc != contacts.end())
	{
		
		penetrationcontacts.emplace(&(*itc), itc->penetration);

		Vector3D r0 = itc->contactPoint - itc->rigidbodies.first->getPosition();
		Vector3D r1 = itc->contactPoint - itc->rigidbodies.second->getPosition();
		Vector3D ObjectSpeed0 = itc->rigidbodies.first->getVitesse() + itc->rigidbodies.first->getRotation() * r0;
		Vector3D ObjectSpeed1 = itc->rigidbodies.second->getVitesse() + itc->rigidbodies.second->getRotation() * r1;
		float speeddif = (ObjectSpeed0 & itc->contactNormal) - (ObjectSpeed1 & itc->contactNormal);

		impulsecontacts.emplace(&(*itc), speeddif);

		itc++;
	}



	//std::cout << "pen size " << penetrationcontacts.size() << "\n";
	//std::cout << "imp size " << impulsecontacts.size() << "\n";


	int loopindex = 0;
	bool contactdetected = penetrationcontacts.size() > 0;


	while (contactdetected && loopindex < 10)
	{

		map<Contact*, int>::iterator itpen = penetrationcontacts.begin();
		Contact* tempcontact = penetrationcontacts.begin()->first;
		float maxpen = tempcontact->penetration;

		while (itpen != penetrationcontacts.end())
		{

			if (itpen->second > maxpen)
			{
				maxpen = itpen->second;
				tempcontact = itpen->first;
			}
			itpen++;
		}


		std::cout << "MAX PENETRATION = 0.01\n";
		if(maxpen > 0.01f)
			SolvePenetration(*tempcontact);
		penetrationcontacts.erase(tempcontact);

		contactdetected = penetrationcontacts.size() > 0;
		loopindex++;
	}




	loopindex = 0;
	contactdetected = impulsecontacts.size() > 0;


	while (contactdetected && loopindex < 10)
	{

		map<Contact*, int>::iterator itimp = impulsecontacts.begin();
		Contact* tempcontact = impulsecontacts.begin()->first;
		float max = impulsecontacts.begin()->second;

		while (itimp != impulsecontacts.end())
		{

			if (itimp->second > max)
			{
				max = itimp->second;
				tempcontact = itimp->first;
			}
			itimp++;
		}


		if (max > 0)
		{
			//std::cout << "IMPULSION DISABLED\n";
			SolveImpulsion(*tempcontact);
			impulsecontacts.erase(tempcontact);
		}
		else
		{
			loopindex = 10;
		}



		contactdetected = impulsecontacts.size() > 0;
		loopindex++;
	}



	}
};


#endif
