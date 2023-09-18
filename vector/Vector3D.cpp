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