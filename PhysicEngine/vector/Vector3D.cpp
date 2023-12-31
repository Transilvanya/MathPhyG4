//
// Created by erwan on 18/09/2023.
//

#include "Vector3D.h"

#include "cmath"


Vector3D::Vector3D() {

    this->vector = {0.0,0.0,0.0};

}

Vector3D::Vector3D(float x, float y, float z) {

    this->vector = {x,y,z};

}

Vector3D::Vector3D(array<float, 3> vector)
{
	this->vector = vector;
}

Vector3D::~Vector3D() {

}

const array<float, 3> Vector3D::getVector() const{

    return vector;
}

const float Vector3D::getX() const{

    return this->vector[0];

}

const float Vector3D::getY() const{

    return this->vector[1];

}

const float Vector3D::getZ() const{

    return this->vector[2];

}

void Vector3D::setX(float x) {

    this->vector[0] = x;

}

void Vector3D::setY(float y) {

    this->vector[1] = y;

}

void Vector3D::setZ(float z) {

    this->vector[2] = z;

}

float Vector3D::getNorm() {

    return (float) sqrt(pow(this->vector[0],2)+pow(this->vector[1],2)+pow(this->vector[2],2));

}

void Vector3D::reset()
{
    this->setX(0);
    this->setY(0);
    this->setZ(0);
}

array<float, 3> Vector3D::getUnitVector() {

    float norm = getNorm();
    return {this->vector[0]/norm,this->vector[1]/norm,this->vector[2]/norm};

}

Vector3D Vector3D::operator+(Vector3D rightVector)
{
    Vector3D nVector = Vector3D();
    nVector.setX(this->getX() + rightVector.getX());
    nVector.setY(this->getY() + rightVector.getY());
    nVector.setZ(this->getZ() + rightVector.getZ());
    return nVector;
}

Vector3D Vector3D::operator-(Vector3D rightVector)
{
    Vector3D nVector = Vector3D();
    nVector.setX(this->getX() - rightVector.getX());
    nVector.setY(this->getY() - rightVector.getY());
    nVector.setZ(this->getZ() - rightVector.getZ());
    return nVector;
}

Vector3D Vector3D::operator*(float scalar)
{
    Vector3D nVector = Vector3D();
    nVector.setX(this->getX() * scalar);
    nVector.setY(this->getY() * scalar);
    nVector.setZ(this->getZ() * scalar);
    return nVector;
}



//produit scalaire
float Vector3D::operator&(Vector3D rightVector)
{
    float returnValue = 0;
    returnValue += this->getX() * rightVector.getX();
    returnValue += this->getY() * rightVector.getY();
    returnValue += this->getZ() * rightVector.getZ();
    return returnValue;
}

//produit vectoriel
Vector3D Vector3D::operator*(Vector3D rightVector)
{
    Vector3D nVector = Vector3D();


    float tempx = getY() * rightVector.getZ() - getZ() * rightVector.getY(); 
    float tempy = getZ() * rightVector.getX() - getX() * rightVector.getZ(); 
    float tempz = getX() * rightVector.getY() - getY() * rightVector.getX(); 

    nVector.setX(tempx);
    nVector.setY(tempy);
    nVector.setZ(tempz);
    return nVector;
}

float Vector3D::distance()
{
    return sqrt(pow(this->getX(),2)+pow(this->getY(),2)+pow(this->getZ(),2));
}

string Vector3D::toString() 
{
    string vector = "";
    for (int i = 0; i < 3; i++)
    {
        vector += std::to_string(this->getVector()[i]);
        vector += " ";
    }
    return vector;

}
