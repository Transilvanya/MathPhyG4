
#ifndef PARTICULECONTACT_CLASS_H
#define PARTICULECONTACT_CLASS_H


class ParticleContact
{

private:
	Particule* particules[2];

	// 0 - 1
	// elasticity of collision
	float restitution;

	//distance of penetration of contact, aka lenght where overlap
	float penetration;


	Vector3D contactNormal;


public:

	ParticleContact(Particule* p1, Particule* p2, float _restitution, float _penetration, Vector3D _contactNormal)
	{
		particules[0] = p1;
		particules[1] = p2;
		restitution = _restitution;
		penetration = _penetration;
		contactNormal = _contactNormal;
	}


	void SolveContact()
	{
		//std::cout << "\n\nsolve contact \n\n\n";
		
		//std::cout << particules[0]->GetName() << " " << particules[0]->getPosition().getX() << " " << particules[0]->getPosition().getY() << " " << particules[0]->getPosition().getZ() << "\n";
		//std::cout << particules[1]->GetName() << " " << particules[1]->getPosition().getX() << " " << particules[1]->getPosition().getY() << " " << particules[1]->getPosition().getZ() << "\n";


		float weight0 = particules[0]->getMasse() / (particules[0]->getMasse() + particules[1]->getMasse());
		float weight1 = particules[1]->getMasse() / (particules[0]->getMasse() + particules[1]->getMasse());

		//std::cout << penetration << " "<< weight0 << " " << weight1 << "\n";


		Vector3D temp0 = contactNormal * weight0 * penetration;
		Vector3D temp1 = contactNormal * -weight1 * penetration;

		//std::cout << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
		//std::cout << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";

		particules[0]->setPosition(particules[0]->getPosition() + temp0);
		particules[1]->setPosition(particules[1]->getPosition() + temp1);

		/* --------------------------------------- */

		Vector3D speeddif = (particules[0]->getVitesse() - particules[1]->getVitesse());


		float k = (restitution + 1) * (speeddif & contactNormal) / (particules[0]->getInverseMasse() + particules[1]->getInverseMasse());


		particules[0]->setVitesse(particules[0]->getVitesse() - contactNormal * (k * particules[0]->getInverseMasse()));
		particules[1]->setVitesse(particules[1]->getVitesse() + contactNormal * (k * particules[1]->getInverseMasse()));

		/*
		std::cout << "\tspeed " << speeddif.getNorm() << "\n";
		std::cout << "\tk " << k << "\n";
		std::cout << "\tcontact normal uniform " << contactNormal.getX() << " " << contactNormal.getY() << " " << contactNormal.getZ() << "\n";

		std::cout << "\tnew speed " << (contactNormal * (k * particules[0]->getInverseMasse())).getX() << " " << (contactNormal * (k * particules[0]->getInverseMasse())).getY() << " " << (contactNormal * (k * particules[0]->getInverseMasse())).getZ() << "\n";

		std::cout << "End Contact\n\n";

		std::cout << particules[0]->GetName() << "\n";
		std::cout << "pos " << particules[0]->getPosition().getX() << " " << particules[0]->getPosition().getY() << " " << particules[0]->getPosition().getZ() << "\n";
		std::cout << "vit " << particules[0]->getVitesse().getX() << " " << particules[0]->getVitesse().getY() << " " << particules[0]->getVitesse().getZ() << "\n";
		std::cout << "vit " << particules[0]->getVitesse().getNorm() << "\n\n";

		std::cout << "\t" << particules[1]->GetName() << "\n";
		std::cout << "\tpos " << particules[1]->getPosition().getX() << " " << particules[1]->getPosition().getY() << " " << particules[1]->getPosition().getZ() << "\n";
		std::cout << "\tvit " << particules[1]->getVitesse().getX() << " " << particules[1]->getVitesse().getY() << " " << particules[1]->getVitesse().getZ() << "\n";
		std::cout << "\tvit " << particules[1]->getVitesse().getNorm() << "\n\n";
		*/
	}


};


#endif
