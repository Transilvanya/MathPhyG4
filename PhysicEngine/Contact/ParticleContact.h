
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

	std::string write()
	{
		std::string s = particules[0]->GetName() + " " + particules[1]->GetName();
		return s;
	}

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

		Vector3D p0vector = particules[0]->getForce();
		Vector3D p1vector = particules[1]->getForce();




		
		//std::cout << particules[0]->GetName() << " " << particules[0]->getPosition().getX() << " " << particules[0]->getPosition().getY() << " " << particules[0]->getPosition().getZ() << "\n";
		//std::cout << particules[1]->GetName() << " " << particules[1]->getPosition().getX() << " " << particules[1]->getPosition().getY() << " " << particules[1]->getPosition().getZ() << "\n";
		

		float weight0 = particules[0]->getMasse()/(particules[0]->getMasse() + particules[1]->getMasse());
		float weight1 = particules[1]->getMasse() / (particules[0]->getMasse() + particules[1]->getMasse());

		//std::cout << penetration << " "<< weight0 << " " << weight1 << "\n";


		Vector3D temp0 = contactNormal* weight0* penetration;
		Vector3D temp1 = contactNormal * -weight1 * penetration;

		//std::cout << temp0.getX() << " " << temp0.getY() << " " << temp0.getZ() << "\n";
		//std::cout << temp1.getX() << " " << temp1.getY() << " " << temp1.getZ() << "\n";

		particules[0]->setPosition(particules[0]->getPosition() + temp0);
		particules[1]->setPosition(particules[1]->getPosition() + temp1);


		/* --------------------------------------- */

		
		Vector3D speeddif = (particules[0]->getVitesse() - particules[1]->getVitesse());
		Vector3D separatingspeed = ( contactNormal * speeddif.getNorm());

		float tempf = particules[0]->getMasse() * particules[0]->getVitesse().getNorm() + particules[1]->getMasse() * particules[1]->getVitesse().getNorm();

		if (tempf != 0)
		{
			// fix

			//float qmvt0 = particules[1]->getMasse() * particules[1]->getVitesse().getNorm() / tempf;
			//float qmvt1 = particules[0]->getMasse() * particules[0]->getVitesse().getNorm() / tempf;
			
			float qmvt0 = particules[1]->getMasse()  / tempf;
			float qmvt1 = particules[0]->getMasse()  / tempf;

			//std::cout << "\t \t " << qmvt0 << "\t" << qmvt1 << "\n";

			particules[0]->setVitesse(particules[0]->getVitesse() + separatingspeed * restitution* qmvt0);
			particules[1]->setVitesse(particules[1]->getVitesse() + separatingspeed * (-1)  *restitution * qmvt1);

		}
		particules[0]->setForce(p0vector);
		particules[1]->setForce(p1vector);

		

		//std::cout << "\n";
	}


};


#endif
