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

	CalculateDerivedData();


	Matrice34 inverseTenseurDerived(InverseTenseur);
	
	inverseTenseurDerived = transformMatrix * inverseTenseurDerived * transformMatrix.Inverse();
	acceleration = ForceSum * inverseMasse ;
	angularacceleration = inverseTenseurDerived * TorqueSum;

	vitesse = vitesse + (acceleration * dt);
	rotation = rotation + (angularacceleration * dt);

	Reset();

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
	