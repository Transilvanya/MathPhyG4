#include "RigidBody.h"

void RigidBody::AddForce(Vector3D force)
{

	this->ForceSum = ForceSum + force;

}

void RigidBody::AddForcePoint(Vector3D force, Vector3D applicationpoint)
{

	Vector3D torque = applicationpoint * force;
	AddForce(force);


}

void RigidBody::AddForceAtBodyPoint(Vector3D force, Vector3D applicationpoint)
{

	Vector3D applicationPosition = applicationpoint - this->position;
	Vector3D torque = applicationPosition * force;
	AddForce(force);



}

void RigidBody::Reset()
{

	this->ForceSum.reset();
	this->TorqueSum.reset();


}

void RigidBody::integrade(float dt)
{
	/*
	std::cout << transformMatrix.getValues(0) << " " << transformMatrix.getValues(1) << " " << transformMatrix.getValues(2) << " " << transformMatrix.getValues(3) << "\n";
	std::cout << transformMatrix.getValues(4) << " " << transformMatrix.getValues(5) << " " << transformMatrix.getValues(6) << " " << transformMatrix.getValues(7) << "\n";
	std::cout << transformMatrix.getValues(8) << " " << transformMatrix.getValues(9) << " " << transformMatrix.getValues(10) << " " << transformMatrix.getValues(11) << "\n\n";
	*/
//	"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n";

	CalculateDerivedData();

	position = position + vitesse * dt;

	orientation = orientation +  (Quaternion(0, rotation.getX(), rotation.getY(), rotation.getZ()) * orientation) * (dt / 2);

	/*
	std::cout << InverseTenseur.getValues(0) << " " << InverseTenseur.getValues(1) << " " << InverseTenseur.getValues(2) << "\n";
	std::cout << InverseTenseur.getValues(3) << " " << InverseTenseur.getValues(4) << " " << InverseTenseur.getValues(5) << "\n";
	std::cout << InverseTenseur.getValues(6) << " " << InverseTenseur.getValues(7) << " " << InverseTenseur.getValues(8) << "\n\n";
	*/

	float v[9] = {	transformMatrix.getValues(0),	transformMatrix.getValues(1),	transformMatrix.getValues(2),
					transformMatrix.getValues(3),	transformMatrix.getValues(4),	transformMatrix.getValues(5),
					transformMatrix.getValues(6),	transformMatrix.getValues(7),	transformMatrix.getValues(8) };

	Matrice33 RotationMatrix(v);

	Matrice33 inverseTenseurDerived(InverseTenseur);
	/*
	std::cout << inverseTenseurDerived.getValues(0) << " " << inverseTenseurDerived.getValues(1) << " " << inverseTenseurDerived.getValues(2) << "\n";
	std::cout << inverseTenseurDerived.getValues(3) << " " << inverseTenseurDerived.getValues(4) << " " << inverseTenseurDerived.getValues(5) << "\n";
	std::cout << inverseTenseurDerived.getValues(6) << " " << inverseTenseurDerived.getValues(7) << " " << inverseTenseurDerived.getValues(8) << "\n\n";
	*/
	//std::cout << inverseTenseurDerived.getValues(0) << " " << inverseTenseurDerived.getValues(1) << " " << inverseTenseurDerived.getValues(2) << " " << inverseTenseurDerived.getValues(3) << "\n";
	//std::cout << inverseTenseurDerived.getValues(4) << " " << inverseTenseurDerived.getValues(5) << " " << inverseTenseurDerived.getValues(6) << " " << inverseTenseurDerived.getValues(7) << "\n";
	//std::cout << inverseTenseurDerived.getValues(8) << " " << inverseTenseurDerived.getValues(9) << " " << inverseTenseurDerived.getValues(10) << " " << inverseTenseurDerived.getValues(11) << "\n\n";


	inverseTenseurDerived = RotationMatrix * inverseTenseurDerived * RotationMatrix.Inverse();
	/*
	std::cout << inverseTenseurDerived.getValues(0) << " " << inverseTenseurDerived.getValues(1) << " " << inverseTenseurDerived.getValues(2) << "\n";
	std::cout << inverseTenseurDerived.getValues(3) << " " << inverseTenseurDerived.getValues(4) << " " << inverseTenseurDerived.getValues(5) << "\n";
	std::cout << inverseTenseurDerived.getValues(6) << " " << inverseTenseurDerived.getValues(7) << " " << inverseTenseurDerived.getValues(8) << "\n\n";
	*/
	acceleration = ForceSum * inverseMasse ;
	angularacceleration = inverseTenseurDerived * TorqueSum;

	vitesse = vitesse + (acceleration * dt);
	rotation = rotation + (angularacceleration * dt);

	Reset();
	
	//std::cout << "_______________\n\n";
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

	//transformMatrix = q.getMatrice34();
	//transformMatrix.getValues(3) = position.getX();
	//transformMatrix.getValues(7) = position.getX();
	//transformMatrix.getValues(11) = position.getZ();



}
	