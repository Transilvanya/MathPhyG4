#pragma once
#ifndef MATHPHYG4_CONTACTSOLVER_H
#define MATHPHYG4_CONTACTSOLVER_H

//solve contact on particules with the list of collisions
class ContactSolver
{
	public:
		ContactSolver();
		~ContactSolver();
		void solveContact(Particules particules, Contact* contactList);

};


#endif // MATHPHYG4_CONTACTSOLVER_H

