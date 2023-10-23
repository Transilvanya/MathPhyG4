#include "CollisionDetector.h"

void CollisionDetector::collisionDetectorApplication(std::map<std::string, Particule*> _physicobjects)
{
	// Get an iterator pointing to the first element in the map
	std::map<std::string, Particule*>::iterator it = _physicobjects.begin();

	// Iterate through the map and print the elements
	while (it != _physicobjects.end())
	{
		// Get an iterator pointing to the first element in the map
		std::map<std::string, Particule*>::iterator it2 = _physicobjects.begin();

		// Iterate through the map and print the elements
		while (it2 != _physicobjects.end())
		{
			if (it->first != it2->first) {
				isColliding(*it->second, *it2->second);
			}
			++it2;
		}
		++it;
	}
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

		contacts.push_back(contact);
	}


}