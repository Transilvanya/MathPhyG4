
#ifndef IFORCE_CLASS_H
#define IFORCE_CLASS_H


#include "../vector/Vector3D.h"
#include "../Particules/Particule.h"
#include <string>
#include <iostream>
class IForce
{
private:
	bool ForceApplied = true;
public:

	struct OutValues
	{
		bool removeforce = false;
		Vector3D outvector = Vector3D(0, 0, 0);
	};

	bool IsForceApplied() { return ForceApplied; }
	void SetForceApplied(bool value) { ForceApplied = value; }
	virtual std::string getType() { return "DefaultForce"; }
	virtual OutValues ApplyForce(Particule* object) { return { false, Vector3D(0, 0, 0) }; }

};


#endif