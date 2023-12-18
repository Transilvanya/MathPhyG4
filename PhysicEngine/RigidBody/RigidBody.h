#pragma once
#ifndef MATHPHYG4_RIGIDBODY_H
#define MATHPHYG4_RIGIDBODY_H
#include "../Vector/Vector3D.h"
#include "../Quaternion/Quaternion.h"
#include "../Matrices/Matrice34.h"
#include "../Matrices/Matrice33.h"

#include <iostream>

enum TypeRigidBody {
	CUBOID,
	SPHERE,
	CYLINDER,
	DEFAULT,
};

class RigidBody
{
public:


	//add a force on center of mass, no torque
	virtual void AddForce(Vector3D force);
	

	//add a force applied to a point in global coordinate. generate force and torque
	//add the force and torque to the sum
	virtual void AddForcePoint(Vector3D force, Vector3D applicationpoint);


	//add a force to a point of the object. the coordinate will be transform in global coordinate before being applied, generate force and torque
	virtual void AddForceAtBodyPoint(Vector3D force, Vector3D applicationpoint);




	//reset ForceSum and TorqueSum
	virtual void Reset();

	//Intergrade the rigid body by modifying the position, orientation and velocity
	virtual void integrade(float dt);



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

	virtual std::string getObjectName() { return ObjectName; }

	virtual float getMasse() { return 1 / inverseMasse; }

	virtual Vector3D getPosition() { return position; }
	virtual Vector3D getVitesse() { return vitesse; }
	virtual Vector3D getRotation() { return rotation; }

	
	virtual float GetVolume() { return 1; }
	virtual void setPosition(Vector3D v) { position = v; }
	virtual float getInverseMasse() { return inverseMasse; }
	virtual void setVitesse(Vector3D v) { vitesse = v; }
	virtual TypeRigidBody getType() { return DEFAULT; };
	
	virtual bool getIsStatic() { return IsStatic; }
	virtual void SetIsStatic(bool value) { IsStatic = value; }

	virtual void setOrientation(Quaternion value) { orientation = value; CalculateDerivedData();}
	virtual void setRotation(Vector3D value) { rotation = value; CalculateDerivedData(); }

	virtual Quaternion getOrientation() { return orientation; }

protected:
	bool IsStatic = false;

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
	float Radius = 0;

	virtual float GetVolume() { return Radius * Radius * Radius * 3.14 * 4/3; }

	RigidSphere(float _Radius, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName) : RigidBody(Masse, _position, _vitesse, _acceleration, orientation, _rotation, _angularacceleration, _ObjectName)
	{

		float value = (2.0f / 5) * Masse * _Radius * _Radius;
		float v[9] = {	value,	0.0f,	0.0f,
						0.0f,	value,	0.0f,
						0.0f,	0.0f,	value };

		Matrice33 m(v);

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

	virtual TypeRigidBody getType()
	{
		return SPHERE;
	}

	float getRadius() { return Radius; }
private:
	
};



class RigidCuboid : public RigidBody
{
public:

	virtual float GetVolume() { return DX * DY * DZ; }

	RigidCuboid(float _DX, float _DY, float _DZ, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName, bool _IsPlane) : RigidBody(Masse, _position, _vitesse, _acceleration, orientation, _rotation, _angularacceleration, _ObjectName)
	{
		IsStatic = _IsPlane;
		if (_IsPlane)
		{
			position = Vector3D(0, position.getY(), 0);
			float v[9] = { 1,	0.0f,	0.0f,
				0.0f,	1,	0.0f,
				0.0f,	0.0f,	1 };

			Matrice33 m(v);
			inverseMasse = 1;
			InverseTenseur = m.Inverse();
		}
		else
		{


			float value1 = (1.0f / 12) * Masse * (_DY * _DY + _DZ * _DZ);
			float value2 = (1.0f / 12) * Masse * (_DX * _DX + _DZ * _DZ);
			float value3 = (1.0f / 12) * Masse * (_DX * _DX + _DY * _DY);

			float v[9] = { value1,	0.0f,	0.0f,
							0.0f,	value2,	0.0f,
							0.0f,	0.0f,	value3 };

			Matrice33 m(v);

			InverseTenseur = m.Inverse();

			DX = _DX;
			DY = _DY;
			DZ = _DZ;
		}
	}

	virtual TypeRigidBody getType()
	{
		
		return CUBOID;
	}

	Vector3D getAxis(int x) {
		switch (x)
		{
		case 0:
			return Vector3D(transformMatrix.getValues(0), transformMatrix.getValues(1), transformMatrix.getValues(2));
		case 1:
			return Vector3D(transformMatrix.getValues(4), transformMatrix.getValues(5), transformMatrix.getValues(6));
		case 2:
			return Vector3D(transformMatrix.getValues(8), transformMatrix.getValues(9), transformMatrix.getValues(10));
		default:
			return Vector3D(0, 0, 0);
		}
	}

	float getOffset()
	{
			return transformMatrix.getValues(7);
			
	}

	Vector3D getNormal() {

		
		float newVal[9]
		{
			transformMatrix.getValues(0), transformMatrix.getValues(1), transformMatrix.getValues(2),
			transformMatrix.getValues(4), transformMatrix.getValues(5), transformMatrix.getValues(6),
			transformMatrix.getValues(8), transformMatrix.getValues(9), transformMatrix.getValues(10)
		};

		Matrice33 m(newVal);
		
		/*

		Vector3D v1 = m * Vector3D(1, 0, 0);
		Vector3D v2 = m * Vector3D(0, 1, 0);
		Vector3D v3 = m * Vector3D(0, 0, 1);
		std::cout << "v1 \t" << v1.getX() << "\t" << v1.getY() << "\t" << v1.getZ() << "\n";
		std::cout << "v2 \t" << v2.getX() << "\t" << v2.getY() << "\t" << v2.getZ() << "\n";
		std::cout << "v3 \t" << v3.getX() << "\t" << v3.getY() << "\t" << v3.getZ() << "\n";
		

		v1 = m * Vector3D(-1, 0, 0);
		v2 = m * Vector3D(0, -1, 0);
		v3 = m * Vector3D(0, 0, -1);
		std::cout << "v1 \t" << v1.getX() << "\t" << v1.getY() << "\t" << v1.getZ() << "\n";
		std::cout << "v2 \t" << v2.getX() << "\t" << v2.getY() << "\t" << v2.getZ() << "\n";
		std::cout << "v3 \t" << v3.getX() << "\t" << v3.getY() << "\t" << v3.getZ() << "\n";

		v1 = m * Vector3D(1, 1, 0);
		v2 = m * Vector3D(0, 1, 1);
		v3 = m * Vector3D(1, 0, 1);
		std::cout << "v1 \t" << v1.getX() << "\t" << v1.getY() << "\t" << v1.getZ() << "\n";
		std::cout << "v2 \t" << v2.getX() << "\t" << v2.getY() << "\t" << v2.getZ() << "\n";
		std::cout << "v3 \t" << v3.getX() << "\t" << v3.getY() << "\t" << v3.getZ() << "\n";

		*/

		Vector3D v = m * Vector3D(0, 1, 0);

		v = v * (1 / v.getNorm());

		//v.setX(-v.getX());

		return v;
	}

	float getDX() { return DX; }
	float getDY() { return DY; }
	float getDZ() { return DZ; }
private:
	float DX = 0;
	float DY = 0;
	float DZ = 0;
};



class RigidCylinder : public RigidBody
{
public:
	virtual float GetVolume() { return Radius * Radius * 3.14 * Height; }

	RigidCylinder(float _Radius, float _Height, float Masse, Vector3D _position, Vector3D _vitesse, Vector3D _acceleration, Quaternion orientation, Vector3D _rotation, Vector3D _angularacceleration, std::string _ObjectName) : RigidBody(Masse, _position, _vitesse, _acceleration, orientation, _rotation, _angularacceleration, _ObjectName)
	{

		float value13 = (1.0f / 4) * Masse * _Radius * _Radius + (1.0f / 12) * Masse * _Height * _Height;
		float value2 = (1.0f / 2) * Masse * _Radius * _Radius;

		float v[9] = { value13,	0.0f,	0.0f,
						0.0f,	value2,	0.0f,
						0.0f,	0.0f,	value13 };

		Matrice33 m(v);



		InverseTenseur = m.Inverse();


		Radius = _Radius;
		Height = _Height;
	}

	virtual TypeRigidBody getType()
	{
		return CYLINDER;
	}

private:
	float Radius = 0;
	float Height = 0;
};


#endif // !MATHPHYG4_RIGIDBODY_H