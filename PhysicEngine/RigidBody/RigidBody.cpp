#include "RigidBody.h"

void RigidBody::AddForce(Vector3D force)
{

	this->ForceSum = ForceSum + force;

}

void RigidBody::AddForcePoint(Vector3D force, Vector3D applicationpoint)
{

	Vector3D torque = applicationpoint * force;

	this->TorqueSum = TorqueSum + torque;
	this->ForceSum = ForceSum + force;
}

void RigidBody::AddForceAtBodyPoint(Vector3D force, Vector3D applicationpoint)
{

	Vector3D applicationPosition = transformMatrix * applicationpoint;
	Vector3D transformedforce = transformMatrix * force;
	Vector3D torque = applicationPosition * transformedforce;

	this->TorqueSum = TorqueSum + torque;
	this->ForceSum = ForceSum + transformedforce;
}

void RigidBody::Reset()
{

	this->ForceSum.reset();
	this->TorqueSum.reset();


}

void RigidBody::integrade(float dt)
{


	
	std::cout << ObjectName << "\n";
	//std::cout << "force " << ForceSum.getX() << " " << ForceSum.getY() << " " << ForceSum.getZ() << "\n";
	//std::cout << "Torque " << TorqueSum.getX() << " " << TorqueSum.getY() << " " << TorqueSum.getZ() << "\n";

	std::cout << "orientation " << orientation.getW() << " " << orientation.getX() << " " << orientation.getY() << " " << orientation.getZ() << "\n";


	


	position = position + vitesse * dt;
	orientation = orientation +  (Quaternion(0, rotation.getX(), rotation.getY(), rotation.getZ()) * orientation) * (dt / 2);

	CalculateDerivedData();


	std::cout << "transformMatrix\n";
	std::cout << transformMatrix.getValues(0) << " " << transformMatrix.getValues(1) << " " << transformMatrix.getValues(2) << " " << transformMatrix.getValues(3) << "\n";
	std::cout << transformMatrix.getValues(4) << " " << transformMatrix.getValues(5) << " " << transformMatrix.getValues(6) << " " << transformMatrix.getValues(7) << "\n";
	std::cout << transformMatrix.getValues(8) << " " << transformMatrix.getValues(9) << " " << transformMatrix.getValues(10) << " " << transformMatrix.getValues(11) << "\n\n";

	/*
	std::cout << InverseTenseur.getValues(0) << " " << InverseTenseur.getValues(1) << " " << InverseTenseur.getValues(2) << "\n";
	std::cout << InverseTenseur.getValues(3) << " " << InverseTenseur.getValues(4) << " " << InverseTenseur.getValues(5) << "\n";
	std::cout << InverseTenseur.getValues(6) << " " << InverseTenseur.getValues(7) << " " << InverseTenseur.getValues(8) << "\n\n";

		float v[9] = { (int)(transformMatrix.getValues(0) * 1000) / 1000.0f,	(int)(transformMatrix.getValues(1) * 1000) / 1000.0f ,	(int)(transformMatrix.getValues(2) * 1000) / 1000.0f ,
					(int)(transformMatrix.getValues(4) * 1000) / 1000.0f ,	(int)(transformMatrix.getValues(5) * 1000) / 1000.0f ,	(int)(transformMatrix.getValues(6) * 1000) / 1000.0f ,
					(int)(transformMatrix.getValues(8) * 1000) / 1000.0f ,	(int)(transformMatrix.getValues(9) * 1000) / 1000.0f ,	(int)(transformMatrix.getValues(10) * 1000) / 1000.0f };
	*/

	float v[9] = { transformMatrix.getValues(0) ,	transformMatrix.getValues(1)  ,	transformMatrix.getValues(2)  ,
					transformMatrix.getValues(4)  ,	transformMatrix.getValues(5) ,	transformMatrix.getValues(6)  ,
					transformMatrix.getValues(8)  ,	transformMatrix.getValues(9) ,	transformMatrix.getValues(10)  };



	Matrice33 RotationMatrix(v);  ///////// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




	Matrice33 inverseTenseurDerived(InverseTenseur);

	
	inverseTenseurDerived = RotationMatrix * inverseTenseurDerived * RotationMatrix.Inverse();
	
	// <<<<<<<<<


	float v2[9];

	for (int i = 0; i < 9; i++)
	{
		v2[i] = (int)(inverseTenseurDerived.getValues(i) * 1000) / 1000.0f;
	}
	inverseTenseurDerived = Matrice33(v2);
	
	std::cout << "inverseTenseurDerived\n";
	std::cout << inverseTenseurDerived.getValues(0) << " " << inverseTenseurDerived.getValues(1) << " " << inverseTenseurDerived.getValues(2) << "\n";
	std::cout << inverseTenseurDerived.getValues(3) << " " << inverseTenseurDerived.getValues(4) << " " << inverseTenseurDerived.getValues(5) << "\n";
	std::cout << inverseTenseurDerived.getValues(6) << " " << inverseTenseurDerived.getValues(7) << " " << inverseTenseurDerived.getValues(8) << "\n\n";
	
	std::cout << "Torque " << TorqueSum.getX() << " " << TorqueSum.getY() << " " << TorqueSum.getZ() << "\n";

	acceleration = ForceSum * inverseMasse ;
	angularacceleration = inverseTenseurDerived * TorqueSum;


	std::cout << "angularacceleration " << angularacceleration.getX() << " " << angularacceleration.getY() << " " << angularacceleration.getZ() << "\n\n";

	

	vitesse = vitesse + (acceleration * dt);
	rotation = rotation + (angularacceleration * dt);

	Reset();

	std::cout << "_______________\n\n";
}

RigidBody::RigidBody(float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{
	float v[9] = {	1.0f,0.0f,0.0f,
					0.0f,1.0f,0.0f,
					0.0f,0.0f,1.0f };
	Matrice33 m(v);
	InverseTenseur = m.Inverse();

	inverseMasse = 1.0f/ Masse;
	position = _position;
	orientation = _orientation;
	vitesse = _vitesse;
	rotation = _rotation;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	ObjectName = _ObjectName;


}

void RigidBody::CalculateDerivedData()
{
	Quaternion q = orientation;
	q.Normalized();

	transformMatrix.SetOrientationAndPosition(q, position);


	float v[12];

	for (int i = 0; i < 12; i++)
	{
		v[i] = (int)(transformMatrix.getValues(i) * 1000) / 1000.0f;
	}
	transformMatrix = Matrice34(v);

	Matrice33 RotationMatrix(v);

	Matrice33 inverseTenseurDerived(InverseTenseur);


}
	