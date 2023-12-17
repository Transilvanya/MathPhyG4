#pragma once
#include "../RigidBody/RigidBody.h"
class Plan
{

private:
    double normalX, normalY, normalZ;
    double distance;

public:
    // Constructeur
    Plan(double nx, double ny, double nz, double d) : normalX(nx), normalY(ny), normalZ(nz), distance(d) {}

    Plan(RigidBody r1, RigidBody r2);


    // Méthode pour générer un nouveau plan en fonction de l'ancien
    Plan generateNewPlan(double offset) const;

    bool isPointOnPositiveSide(RigidBody p) const;


    // Méthode pour afficher les propriétés du plan
    void display() const {
        std::cout << "Plan: Normal(" << normalX << ", " << normalY << ", " << normalZ << "), Distance: " << distance << std::endl;
    }
};

