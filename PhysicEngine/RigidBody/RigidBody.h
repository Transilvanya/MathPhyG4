#pragma once
#ifndef MATHPHYG4_RIGIDBODY_H
#define MATHPHYG4_RIGIDBODY_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"
#include "../Matrices/Matrice34.h"
#include "../Matrices/Matrice33.h"

class RigidBody
{
public:


	//add a force on center of mass, no torque
	void AddForce(Vector3D force);
	

	//add a force applied to a point in global coordinate. generate force and torque
	//add the force and torque to the sum
	void AddForcePoint(Vector3D force, Vector3D applicationpoint);
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
	void AddForceAtBodyPoint(Vector3D force, Vector3D applicationpoint);




	//reset ForceSum and TorqueSum
	void Reset();

	//Intergrade the rigid body by modifying the position, orientation and velocity
	void Intergrate(float dt);

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

	RigidBody(Matrice33 _InverseTenseur, std::string _Type, float _inverseMasse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Vector3D _rotation, Vector3D _angularvitesse, Vector3D _angularacceleration, std::string _ObjectName);




	//getters, setters



	//used by GraphicEngine
	virtual Vector3D getDeltaPosition();
	virtual Vector3D getPrevPosition();

	virtual Vector3D getDeltaRotation();
	virtual Vector3D getPrevRotation();

private:
	//sum of all the force at each tick
	Vector3D ForceSum;
	//sum of all the torque at each tick
	Vector3D TorqueSum;

	//to define during creation of rigidbody in physicengine
	Matrice33 InverseTenseur;

	std::string Type;

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



	//only for dysplay puprose
	Vector3D PrevPosition;
	Vector3D PrevRotation;


	Matrice34 transformMatrix;

	//appel a chaque frame
	//calcule le transformeMatrice
	//and normalize the orientation
	//create the transformMatrix using the orientation and the position
	void CalculateDerivedData();

	//get the Tenseur in global coordinate;
		//check that it doesn't change at position(0,0,0) rotation (0,0,0)
		//should not be affected by the position of the object
	Matrice33 GetInverseTenseur();
};
#endif // !MATHPHYG4_RIGIDBODY_H