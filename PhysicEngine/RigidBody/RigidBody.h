#pragma once
#ifndef MATHPHYG4_RIGIDBODY_H
#define MATHPHYG4_RIGIDBODY_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"
#include "../Matrices/Matrice34.h"
#include "../Matrices/Matrice33.h"

#include <iostream>

class RigidBody
{
public:


	//add a force on center of mass, no torque
	virtual void AddForce(Vector3D force);
	

	//add a force applied to a point in global coordinate. generate force and torque
	//add the force and torque to the sum
	virtual void AddForcePoint(Vector3D force, Vector3D applicationpoint);
	/*
	check that it create only torque and no force, check in local and global coordinates

		  |->
		  |     
		<-|

	check that it create torque and force
	|->
	|
	|

	check that that it create force but that the torque negate each other
	|->
	|
	|->

	*/

	//add a force to a point of the object. the coordinate will be transform in global coordinate before being applied, generate force and torque
	virtual void AddForceAtBodyPoint(Vector3D force, Vector3D applicationpoint);




	//reset ForceSum and TorqueSum
	virtual void Reset();

	//Intergrade the rigid body by modifying the position, orientation and velocity
	virtual void integrade(float dt);

	/*
	|..		   .|.    ..|
	|..->   => .|. => ..|
	|..		   .|.    ..|
	*/


	/*
	test rotation, apply force in global coordinate and local coordinate

		  |->
		  |     =>  -----
		<-|

	*/

	RigidBody(float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration,Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName);


	//appel a chaque frame
//calcule le transformeMatrice
//and normalize the orientation
//create the transformMatrix using the orientation and the position
	void CalculateDerivedData();

	//get the Tenseur in global coordinate;
		//check that it doesn't change at position(0,0,0) rotation (0,0,0)
		//should not be affected by the position of the object
	virtual Matrice33 GetInverseTenseur()
	{
		return InverseTenseur;
	}

	//getters, setters

	virtual Matrice34 GettransformMatrix() 
	{
		return transformMatrix;
	}

	virtual std::string GetName() { return ObjectName; }

protected:
	//sum of all the force at each tick
	Vector3D ForceSum;
	//sum of all the torque at each tick
	Vector3D TorqueSum;

	//to define during creation of rigidbody in physicengine
	Matrice33 InverseTenseur;

	std::string ObjectName;

	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D vitesse;
	Vector3D acceleration;


	Quaternion orientation;
	//angular speed
	Vector3D rotation;
	Vector3D angularacceleration;



	Matrice34 transformMatrix;


};



class RigidSphere : public RigidBody
{
public:

	RigidSphere(float _Radius, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName) : RigidBody(Masse, _position, _vitesse, _acceleration, orientation, _rotation, _angularacceleration, _ObjectName)
	{

		float value = (2.0f / 5) * Masse * _Radius * _Radius;
		float v[9] = {	value,	0.0f,	0.0f,
						0.0f,	value,	0.0f,
						0.0f,	0.0f,	value };

		Matrice33 m(v);
	//	std::cout << "____ _ _ _ \n\n";

		std::cout << "\n";
		std::cout << m.getValues(0) << " " << m.getValues(1) << " " << m.getValues(2) << "\n";
		std::cout << m.getValues(3) << " " << m.getValues(4) << " " << m.getValues(5) << "\n";
		std::cout << m.getValues(6) << " " << m.getValues(7) << " " << m.getValues(8) << "\n\n";


		InverseTenseur = m.Inverse();

		std::cout << "\n";
		std::cout << InverseTenseur.getValues(0) << " " << InverseTenseur.getValues(1) << " " << InverseTenseur.getValues(2) << "\n";
		std::cout << InverseTenseur.getValues(3) << " " << InverseTenseur.getValues(4) << " " << InverseTenseur.getValues(5) << "\n";
		std::cout << InverseTenseur.getValues(6) << " " << InverseTenseur.getValues(7) << " " << InverseTenseur.getValues(8) << "\n\n";

		std::cout << "____ _ _ _ \n\n";

		Radius = _Radius;
	}

private:
	float Radius = 0;
};

#endif // !MATHPHYG4_RIGIDBODY_H