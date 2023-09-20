//
// Created by erwan on 18/09/2023.
//

#ifndef MATHPHYG4_VECTOR3D_H
#define MATHPHYG4_VECTOR3D_H

#include <array>

using namespace std;

class Vector3D {


public :

    //constructor
    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(array<float,3> vector);


    //Destructor
    ~Vector3D();


    //setter
    void setX(float x);
    void setY(float y);
    void setZ(float z);


    // getter
    float getX();
    float getY();
    float getZ();
    array<float,3> getVector();

    //method
    float getNorm();
    array<float,3> getUnitVector();
    Vector3D operator+(Vector3D rightVector);
    Vector3D operator-(Vector3D rightVector);
    Vector3D operator*(int scalar);
    int operator&(Vector3D rightVector);
    Vector3D operator*(Vector3D rightVector);


private :
    std::array<float,3> vector{};


};


#endif //MATHPHYG4_VECTOR3D_H
