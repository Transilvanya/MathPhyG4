




#include "MainEngine/MainEngine.h"
#include "PhysicEngine/PhysicEngine.h"
#include "GraphicEngine/GraphicEngine.h"

/* -- static init -- */

MainEngine* MainEngine::_mainmanagerptr = NULL;
PhysicEngine* PhysicEngine::_physicengineptr = NULL;
GraphicEngine* GraphicEngine::_graphicengineptr = NULL;

/* -- ----------- -- */

/*


*/


void SwitchPerspective()
{
	GraphicEngine::GetInstance()->SwitchPersp();
}

int main()
{



	return 0;
}