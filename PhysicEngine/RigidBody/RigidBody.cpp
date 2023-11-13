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

void RigidBody::Intergrate(float dt)
{

	//update position
	PrevPosition = position;
	position = position + (vitesse * dt);

	//update angle	
	PrevRotation = rotation;
	rotation = rotation + (angularacceleration * dt);

	CalculateDerivedData();


	Matrice34 inverseTenseurDerived(InverseTenseur);
	
	inverseTenseurDerived = transformMatrix * inverseTenseurDerived * transformMatrix.Inverse();
	acceleration = ForceSum * inverseMasse ;
	angularacceleration = inverseTenseurDerived * TorqueSum;

	vitesse = vitesse + (acceleration * dt);
	rotation = rotation + (angularacceleration * dt);

	Reset();

}

RigidBody::RigidBody(Matrice33 _InverseTenseur, std::string _Type, float _inverseMasse, Vector3D _position, Vector3D _acceleration, Quaternion _orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName)
{

	InverseTenseur = _InverseTenseur;
	Type = _Type;
	inverseMasse = _inverseMasse;
	position = _position;
	orientation = _orientation;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	ObjectName = _ObjectName;


}

void RigidBody::CalculateDerivedData()
{
	Quaternion q = orientation;
	q.Normalized();
	transformMatrix = q.getMatrice34();
	transformMatrix.getValues(3) = position.getX();
	transformMatrix.getValues(7) = position.getX();
	transformMatrix.getValues(11) = position.getZ();



}
	