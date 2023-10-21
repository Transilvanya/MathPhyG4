#include "ParticleContactResolver.h"

	//take an array of contact
	//iterate on each contact accorcind to their sepatating velocity
	//stop when all caontacts are solvent or when we reach the max iteration
void ParticleContactResolver::resolveContacts(ParticleContact* contactArray,
	unsigned int numContacts,
	float duration) {
	int i = 0;
	for (i = 0; i < this->iterations; i++) {
		float max = 0;
		int maxIndex = numContacts;
		for (int j = 0; j < numContacts; j++) {
			float sepVel = contactArray[j].calculateSeparatingVelocity();
			if (sepVel < max) {
				max = sepVel;
				maxIndex = j;
			}
		}
		contactArray[maxIndex].resolve(duration);
	}
}