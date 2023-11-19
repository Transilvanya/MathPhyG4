
#ifndef IFORCERIGID_CLASS_H
#define IFORCERIGID_CLASS_H


#include "../vector/Vector3D.h"
#include "../RigidBody/RigidBody.h"
#include <string>
#include <iostream>
class IForceRigid
{
private:
	bool ForceApplied = true;

	Vector3D force = Vector3D(0, 0, 0);
public:
	
	struct OutValues {
		bool removeforce = false;
		Vector3D outVector = Vector3D(0, 0, 0);
	};


	bool IsForceApplied() { return ForceApplied; }
	void SetForceApplied(bool value) { this->ForceApplied = value; }
	virtual std::string getType() = 0;
	//the return define wheater the force should be removed after this tick
	virtual OutValues ApplyForce(RigidBody* object) { return {false, force }; }

};


#endif