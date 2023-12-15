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



	float v[9] = { transformMatrix.getValues(0) ,	transformMatrix.getValues(1)  ,	transformMatrix.getValues(2)  ,
					transformMatrix.getValues(4)  ,	transformMatrix.getValues(5) ,	transformMatrix.getValues(6)  ,
					transformMatrix.getValues(8)  ,	transformMatrix.getValues(9) ,	transformMatrix.getValues(10) };



	Matrice33 RotationMatrix(v);

	Vector3D transformedforce = RotationMatrix * force;
	
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


	/*
	std::cout << ObjectName << "\n";
	std::cout << "force " << ForceSum.getX() << " " << ForceSum.getY() << " " << ForceSum.getZ() << "\n";
	std::cout << "Torque " << TorqueSum.getX() << " " << TorqueSum.getY() << " " << TorqueSum.getZ() << "\n";

	std::cout << "position " << position.getX() << " " << position.getY() << " " << position.getZ() << "\n";
	std::cout << "orientation " << orientation.getW() << " " << orientation.getX() << " " << orientation.getY() << " " << orientation.getZ() << "\n";

	*/
	

	std::cout << "\t\t" << ObjectName << "\n";
	//std::cout << "position " << position.getX() << " " << position.getY() << " " << position.getZ() << "\n";
	//std::cout << "orientation " << orientation.getW() << " " << orientation.getX() << " " << orientation.getY() << " " << orientation.getZ() << "\n";
	//std::cout << "vitesse " << vitesse.getX() << " " << vitesse.getY() << " " << vitesse.getZ() << "\n";
	std::cout << "\t\t" << "rotation " << rotation.getX() << " " << rotation.getY() << " " << rotation.getZ() << "\n";
	std::cout << "\t\t" << "\n";

	position = position + vitesse * dt;
	orientation = orientation +  (Quaternion(0, rotation.getX(), rotation.getY(), rotation.getZ()) * orientation) * (dt / 2);

	while (orientation.getW() > 100)
		orientation.setW(orientation.getW() - 100.0f);
	while (orientation.getX() > 100)
		orientation.setX(orientation.getX() - 100.0f);
	while (orientation.getY() > 100)
		orientation.setY(orientation.getY() - 100.0f);
	while (orientation.getZ() > 100)
		orientation.setZ(orientation.getZ() - 100.0f);

	while (orientation.getW() < -100)
		orientation.setW(orientation.getW() + 100.0f);
	while (orientation.getX() < -100)
		orientation.setX(orientation.getX() + 100.0f);
	while (orientation.getY() < -100)
		orientation.setY(orientation.getY() + 100.0f);
	while (orientation.getZ() < -100)
		orientation.setZ(orientation.getZ() + 100.0f);

	CalculateDerivedData();

	
	/*
	std::cout << "transformMatrix\n";
	std::cout << transformMatrix.getValues(0) << " " << transformMatrix.getValues(1) << " " << transformMatrix.getValues(2) << " " << transformMatrix.getValues(3) << "\n";
	std::cout << transformMatrix.getValues(4) << " " << transformMatrix.getValues(5) << " " << transformMatrix.getValues(6) << " " << transformMatrix.getValues(7) << "\n";
	std::cout << transformMatrix.getValues(8) << " " << transformMatrix.getValues(9) << " " << transformMatrix.getValues(10) << " " << transformMatrix.getValues(11) << "\n\n";
	*/
	

	float v[9] = { transformMatrix.getValues(0) ,	transformMatrix.getValues(1)  ,	transformMatrix.getValues(2)  ,
					transformMatrix.getValues(4)  ,	transformMatrix.getValues(5) ,	transformMatrix.getValues(6)  ,
					transformMatrix.getValues(8)  ,	transformMatrix.getValues(9) ,	transformMatrix.getValues(10)  };



	Matrice33 RotationMatrix(v); 




	Matrice33 inverseTenseurDerived(InverseTenseur);

	inverseTenseurDerived = RotationMatrix.Inverse() * inverseTenseurDerived * RotationMatrix;
	//inverseTenseurDerived = RotationMatrix * inverseTenseurDerived * RotationMatrix.Inverse();
	
	// <<<<<<<<<
	
	/*
	std::cout << "InverseTenseur\n";
	std::cout << InverseTenseur.getValues(0) << " " << InverseTenseur.getValues(1) << " " << InverseTenseur.getValues(2) << "\n";
	std::cout << InverseTenseur.getValues(3) << " " << InverseTenseur.getValues(4) << " " << InverseTenseur.getValues(5) << "\n";
	std::cout << InverseTenseur.getValues(6) << " " << InverseTenseur.getValues(7) << " " << InverseTenseur.getValues(8) << "\n\n";

	std::cout << "RotationMatrix\n";
	std::cout << RotationMatrix.getValues(0) << " " << RotationMatrix.getValues(1) << " " << RotationMatrix.getValues(2) << "\n";
	std::cout << RotationMatrix.getValues(3) << " " << RotationMatrix.getValues(4) << " " << RotationMatrix.getValues(5) << "\n";
	std::cout << RotationMatrix.getValues(6) << " " << RotationMatrix.getValues(7) << " " << RotationMatrix.getValues(8) << "\n\n";

	std::cout << "inverseTenseurDerived\n";
	std::cout << inverseTenseurDerived.getValues(0) << " " << inverseTenseurDerived.getValues(1) << " " << inverseTenseurDerived.getValues(2) << "\n";
	std::cout << inverseTenseurDerived.getValues(3) << " " << inverseTenseurDerived.getValues(4) << " " << inverseTenseurDerived.getValues(5) << "\n";
	std::cout << inverseTenseurDerived.getValues(6) << " " << inverseTenseurDerived.getValues(7) << " " << inverseTenseurDerived.getValues(8) << "\n\n";
	*/
	
	

	acceleration = ForceSum * inverseMasse ;
	angularacceleration = inverseTenseurDerived * TorqueSum;


	vitesse = vitesse + (acceleration * dt);

	vitesse.setX(max(vitesse.getX(), -100.0f));
	vitesse.setY(max(vitesse.getY(), -100.0f));
	vitesse.setZ(max(vitesse.getZ(), -100.0f));

	vitesse.setX(min(vitesse.getX(),  100.0f));
	vitesse.setY(min(vitesse.getY(),  100.0f));
	vitesse.setZ(min(vitesse.getZ(),  100.0f));

	rotation = rotation + (angularacceleration * dt);

	rotation.setX(max(rotation.getX(), -100.0f));
	rotation.setY(max(rotation.getY(), -100.0f));
	rotation.setZ(max(rotation.getZ(), -100.0f));

	rotation.setX(min(rotation.getX(),  100.0f));
	rotation.setY(min(rotation.getY(),  100.0f));
	rotation.setZ(min(rotation.getZ(),  100.0f));

	Reset();



	/*
	std::cout << "acceleration " << acceleration.getX() << " " << acceleration.getY() << " " << acceleration.getZ() << "\n";
	std::cout << "angularacceleration " << angularacceleration.getX() << " " << angularacceleration.getY() << " " << angularacceleration.getZ() << "\n";
	std::cout << "_______________\n\n";
	*/
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

}
	