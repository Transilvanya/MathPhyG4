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

Vector3D::~Vector3D() {

}

array<float, 3> Vector3D::getVector() {

    return vector;
}

float Vector3D::getX() {

    return this->vector[0];

}

float Vector3D::getY() {

    return this->vector[1];

}

float Vector3D::getZ() {

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
    returnValue += this->getX() + rightVector.getX();
    returnValue += this->getY() + rightVector.getY();
    returnValue += this->getZ() + rightVector.getZ();
    return returnValue;
}

Vector3D Vector3D::operator*(Vector3D rightVector)
{
    Vector3D nVector = Vector3D();
    nVector.setX(this->getY() * rightVector.getZ() - this->getZ() * rightVector.getY());
    nVector.setY(this->getX() * rightVector.getZ() - this->getZ() * rightVector.getX());
    nVector.setZ(this->getX() * rightVector.getY() - this->getY() * rightVector.getX());
    return Vector3D();
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
