
#ifndef PARTICULECONTACT_CLASS_H
#define PARTICULECONTACT_CLASS_H

#include "../Particules/Particule.h"

class ParticleContact
{

private:
	Particule* rigidbodies[2];

	// 0 - 1
	// elasticity of collision
	float restitution;

	//distance of penetration of contact, aka lenght where overlap
	float penetration;


	Vector3D contactNormal;


public:

	ParticleContact(Particule* p1, Particule* p2, float _restitution, float _penetration, Vector3D _contactNormal)
	{
		rigidbodies[0] = p1;
		rigidbodies[1] = p2;
		restitution = _restitution;
		penetration = _penetration;
		contactNormal = _contactNormal;
	}


	void SolveContact()
	{
		//std::cout << "\n\nsolve contact \n\n\n";
		
		//std::cout << rigidbodies[0]->GetName() << " " << rigidbodies[0]->getPosition().getX() << " " << rigidbodies[0]->getPosition().getY() << " " << rigidbodies[0]->getPosition().getZ() << "\n";
		//std::cout << rigidbodies[1]->GetName() << " " << rigidbodies[1]->getPosition().getX() << " " << rigidbodies[1]->getPosition().getY() << " " << rigidbodies[1]->getPosition().getZ() << "\n";


		float weight0 = rigidbodies[0]->getMasse() / (rigidbodies[0]->getMasse() + rigidbodies[1]->getMasse());
		float weight1 = rigidbodies[1]->getMasse() / (rigidbodies[0]->getMasse() + rigidbodies[1]->getMasse());

		//std::cout << penetration << " "<< weight0 << " " << weight1 << "\n";


		Vector3D temp0 = contactNormal * weight0 * penetration;
		Vector3D temp1 = contactNormal * -weight1 * penetration;

		//std::cout << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
		//std::cout << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";

		rigidbodies[0]->setPosition(rigidbodies[0]->getPosition() + temp0);
		rigidbodies[1]->setPosition(rigidbodies[1]->getPosition() + temp1);

		/* --------------------------------------- */

		Vector3D speeddif = (rigidbodies[0]->getVitesse() - rigidbodies[1]->getVitesse());


		float k = (restitution + 1) * (speeddif & contactNormal) / (rigidbodies[0]->getInverseMasse() + rigidbodies[1]->getInverseMasse());


		rigidbodies[0]->setVitesse(rigidbodies[0]->getVitesse() - contactNormal * (k * rigidbodies[0]->getInverseMasse()));
		rigidbodies[1]->setVitesse(rigidbodies[1]->getVitesse() + contactNormal * (k * rigidbodies[1]->getInverseMasse()));

		/*
		std::cout << "\tspeed " << speeddif.getNorm() << "\n";
		std::cout << "\tk " << k << "\n";
		std::cout << "\tcontact normal uniform " << contactNormal.getX() << " " << contactNormal.getY() << " " << contactNormal.getZ() << "\n";

		std::cout << "\tnew speed " << (contactNormal * (k * rigidbodies[0]->getInverseMasse())).getX() << " " << (contactNormal * (k * rigidbodies[0]->getInverseMasse())).getY() << " " << (contactNormal * (k * rigidbodies[0]->getInverseMasse())).getZ() << "\n";

		std::cout << "End Contact\n\n";

		std::cout << rigidbodies[0]->GetName() << "\n";
		std::cout << "pos " << rigidbodies[0]->getPosition().getX() << " " << rigidbodies[0]->getPosition().getY() << " " << rigidbodies[0]->getPosition().getZ() << "\n";
		std::cout << "vit " << rigidbodies[0]->getVitesse().getX() << " " << rigidbodies[0]->getVitesse().getY() << " " << rigidbodies[0]->getVitesse().getZ() << "\n";
		std::cout << "vit " << rigidbodies[0]->getVitesse().getNorm() << "\n\n";

		std::cout << "\t" << rigidbodies[1]->GetName() << "\n";
		std::cout << "\tpos " << rigidbodies[1]->getPosition().getX() << " " << rigidbodies[1]->getPosition().getY() << " " << rigidbodies[1]->getPosition().getZ() << "\n";
		std::cout << "\tvit " << rigidbodies[1]->getVitesse().getX() << " " << rigidbodies[1]->getVitesse().getY() << " " << rigidbodies[1]->getVitesse().getZ() << "\n";
		std::cout << "\tvit " << rigidbodies[1]->getVitesse().getNorm() << "\n\n";
		*/
	}


};


#endif
