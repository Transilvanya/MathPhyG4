#include "Particules.h"

void Particules::intergrade() {
	this->vectorPosition = this->vectorPosition + (this->vectorVitesse * DT);
	this->vectorVitesse = this->vectorVitesse * damping + (this->vectorAcceleration * DT);
}
