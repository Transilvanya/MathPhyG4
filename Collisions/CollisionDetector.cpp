#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{

}

CollisionDetector::~CollisionDetector()
{
}

void CollisionDetector::isColliding(Particule part1, Particule part2)
{
	//on prend les positions des particules
	Vector3D pos1 = part1.getPosition();
	Vector3D pos2 = part2.getPosition();
	//distance entre les deux particules
	float distance = sqrt(pow(pos1.getX() - pos2.getX(), 2) + pow(pos1.getY() - pos2.getY(), 2) + pow(pos1.getZ() - pos2.getZ(), 2));

	//si la distance est inferieur a la somme des rayons des particules
	if (2 < distance) {
		ParticleContact contact;
		contact.particule[0] = &part1;
		contact.particule[1] = &part2;

		contacts.emplace(nbContact, contact);
		nbContact++;
	}


}