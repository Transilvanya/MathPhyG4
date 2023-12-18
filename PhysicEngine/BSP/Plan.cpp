#include "Plan.h"


Plan Plan::generateNewPlan(double offset) const {
    // Ajouter un décalage à la distance du plan existant
    double newDistance = distance + offset;

    // Créer un nouveau plan avec les mêmes normales mais une distance mise à jour
    Plan newPlan(normalX, normalY, normalZ, newDistance);

    return newPlan;
}

bool Plan::isPointOnPositiveSide(RigidBody* r) const {
    double distanceToPoint = normalX * r->getPosition().getX() + normalY * r->getPosition().getY() + normalZ * r->getPosition().getZ() - distance;
    return distanceToPoint > 0.0;
}

int Plan::isAreaOnPositiveSide(RigidBody* r) const {




    double distanceToPoint = normalX * r->getPosition().getX() + normalY * r->getPosition().getY() + normalZ * r->getPosition().getZ() - distance;
    double radius = 0;
    /*
    if (dynamic_cast<RigidCylinder*>(r)) {
        RigidCylinder* c = (RigidCylinder*)r;
        radius = sqrt(pow(sqrt(2 * pow(c->getRadius(), 2)), 2) + pow(c->getHeight(), 2));
    }
    else 
        */
        if (dynamic_cast<RigidCuboid*>(r)) {
        RigidCuboid* c = (RigidCuboid*)r;
        radius = sqrt(pow(c->getDX(), 2) + pow(c->getDY(), 2) + pow(c->getDY(), 2));
    }
    else if (dynamic_cast<RigidSphere*>(r)) {
        RigidSphere* s = (RigidSphere*)r;
        radius = s->Radius;
    }
    
    if (abs(distanceToPoint) < radius)return 2;
    else return distanceToPoint > 0.0;
    
}

Plan::Plan(RigidBody* r1, RigidBody *r2) {
    // Calculer le vecteur normal en utilisant la différence entre les deux points
    normalX = r1->getPosition().getX() - r2->getPosition().getX();
    normalY = r1->getPosition().getY() - r2->getPosition().getY();
    normalZ = r1->getPosition().getZ() - r2->getPosition().getZ();

    // Normaliser le vecteur normal
    double length = std::sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
    normalX /= length;
    normalY /= length;
    normalZ /= length;

    // Calculer la distance du plan par rapport au milieu de la ligne formée par les deux points
    double midX = (r1->getPosition().getX() + r2->getPosition().getX()) / 2.0;
    double midY = (r1->getPosition().getY() + r2->getPosition().getY()) / 2.0;
    double midZ = (r1->getPosition().getZ() + r2->getPosition().getZ()) / 2.0;

    distance = normalX * midX + normalY * midY + normalZ * midZ;
}