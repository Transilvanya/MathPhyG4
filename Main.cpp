




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


void SetupObject()
{
	GraphicEngine::GetInstance()->CreateSphere("sphere3", "simplecolor", 1, -0.5f, 0, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere4", "simplecolor", 1, 2, 0, 0, 1, 1, 1, 1);

	GraphicEngine::GetInstance()->CreateSphere("sphere5", "simplecolor", 1, 10, 6, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere6", "simplecolor", 1, 0, 5, 0, 1, 1, 1, 1);

	GraphicEngine::GetInstance()->CreateSphere("sphere7", "simplecolor", 1, -10, 1, 0, 1, 1, 1, 1);


	PhysicEngine::GetInstance()->CreateParticule(Vector3D(-0.5f, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 200, "particule3");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(2, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 50, "particule4");

	PhysicEngine::GetInstance()->CreateParticule(Vector3D(10, 6, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 50, "particule5");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 5, 0), Vector3D(3, 0, 0), Vector3D(0, 0, 0), 100, "particule6");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(-10, 1, 0), Vector3D(3, 0, 0), Vector3D(0, 0, 0), 100, "particule7");


	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule3"), GraphicEngine::GetInstance()->GetGraphicObject("sphere3"), "entity3");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule4"), GraphicEngine::GetInstance()->GetGraphicObject("sphere4"), "entity4");

	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule5"), GraphicEngine::GetInstance()->GetGraphicObject("sphere5"), "entity5");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule6"), GraphicEngine::GetInstance()->GetGraphicObject("sphere6"), "entity6");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule7"), GraphicEngine::GetInstance()->GetGraphicObject("sphere7"), "entity7");


	PhysicEngine::GetInstance()->GetLinkRegistry()->CreateRod(PhysicEngine::GetInstance()->GetParticule("particule5"), PhysicEngine::GetInstance()->GetParticule("particule6"), "link1", 5, false);
	PhysicEngine::GetInstance()->GetLinkRegistry()->CreateRod(PhysicEngine::GetInstance()->GetParticule("particule6"), PhysicEngine::GetInstance()->GetParticule("particule4"), "link2", 5, true);


	PhysicEngine::GetInstance()->GetLinkRegistry()->CreateAnchor(PhysicEngine::GetInstance()->GetParticule("particule5"), Vector3D(10, 6, 0), "anchor1", 1, false);
}

void DeleteObject()
{
	MainEngine::GetInstance()->RemoveEntity("entity1");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere");
	PhysicEngine::GetInstance()->RemoveParticule("particule");

	MainEngine::GetInstance()->RemoveEntity("entity2");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere2");
	PhysicEngine::GetInstance()->RemoveParticule("particule2");

	MainEngine::GetInstance()->RemoveEntity("entity3");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere3");
	PhysicEngine::GetInstance()->RemoveParticule("particule3");

	MainEngine::GetInstance()->RemoveEntity("entity4");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere4");
	PhysicEngine::GetInstance()->RemoveParticule("particule4");

	MainEngine::GetInstance()->RemoveEntity("entity5");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere5");
	PhysicEngine::GetInstance()->RemoveParticule("particule5");

	MainEngine::GetInstance()->RemoveEntity("entity6");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere6");
	PhysicEngine::GetInstance()->RemoveParticule("particule6");


	MainEngine::GetInstance()->RemoveEntity("entity7");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere7");
	PhysicEngine::GetInstance()->RemoveParticule("particule7");

	PhysicEngine::GetInstance()->GetLinkRegistry()->RemoveLink("link1");
	PhysicEngine::GetInstance()->GetLinkRegistry()->RemoveLink("link2");

	PhysicEngine::GetInstance()->GetLinkRegistry()->RemoveAnchor("anchor1");
}
//

void SetupObjectForce()
{
	GraphicEngine::GetInstance()->CreateSphere("sphere", "simplecolor", 1, 0, 3, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere2", "simplecolor", 1, 10, 0, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere3", "simplecolor", 1, -10, 0, 0, 1, 1, 1, 1);



	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 3, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 200, "particule");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(10, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 300, "particule2");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(-10, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 10, "particule3");



	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule"), GraphicEngine::GetInstance()->GetGraphicObject("sphere"), "entity1");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule2"), GraphicEngine::GetInstance()->GetGraphicObject("sphere2"), "entity2");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule3"), GraphicEngine::GetInstance()->GetGraphicObject("sphere3"), "entity3");


	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceGravityToParticule(PhysicEngine::GetInstance()->GetParticule("particule"), "gravity1");
	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceDragToParticule(0.4f, 0.2f, PhysicEngine::GetInstance()->GetParticule("particule"), "drag");
	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceBuoyancyToParticule(0, 1000, PhysicEngine::GetInstance()->GetParticule("particule"), "buoyancy1");


	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceGravityToParticule(PhysicEngine::GetInstance()->GetParticule("particule2"), "gravity1");
	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceDragToParticule(0.4f, 0.2f, PhysicEngine::GetInstance()->GetParticule("particule2"), "drag");
	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceBuoyancyToParticule(0, 1000, PhysicEngine::GetInstance()->GetParticule("particule2"), "buoyancy1");

	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceSpringToParticule(10, 5, 15, false,
		PhysicEngine::GetInstance()->GetParticule("particule"),
		PhysicEngine::GetInstance()->GetParticule("particule2"),
		"spring"
	);


	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceSpringFixedToParticule(Vector3D(-7, 5, 0), 10, 2, 1000, true, PhysicEngine::GetInstance()->GetParticule("particule3"), "fixedspring");
}

void DeleteObjectForce()
{
	MainEngine::GetInstance()->RemoveEntity("entity1");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere");
	PhysicEngine::GetInstance()->RemoveParticule("particule");

	MainEngine::GetInstance()->RemoveEntity("entity2");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere2");
	PhysicEngine::GetInstance()->RemoveParticule("particule2");



	
}


void SwitchPerspective()
{
	GraphicEngine::GetInstance()->SwitchPersp();
}

int main()
{


	GraphicEngine::GetInstance()->Init();

	PhysicEngine::GetInstance()->Init();

	MainEngine::GetInstance()->Init();


	std::vector<GLfloat> groundvertice =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-20.0f, 0.0f, -20.0f,   0.83f, 0.70f, 0.44f,	0.7f,
		-20.0f, 0.0f,  20.0f,	0.83f, 0.70f, 0.44f,	0.7f,
		 20.0f, 0.0f,  20.0f,   0.83f, 0.70f, 0.44f,	0.7f,
		 20.0f, 0.0f, -20.0f,   0.83f, 0.70f, 0.44f,	0.7f,
	};
	std::vector<GLuint> groundindice =
	{
		0, 1, 2,
		0, 2, 3,
	};



	GraphicEngine::GetInstance()->CreateShader("simplecolor", "GraphicEngine/OpenGL/Shaders/simplecolor.vert", "GraphicEngine/OpenGL/Shaders/simplecolor.frag");

	GraphicEngine::GetInstance()->CreatePolygon("newobject", "simplecolor", groundindice, groundvertice);


	SetupObject();



	std::list<std::string> lst = MainEngine::GetInstance()->GetEntities();

	std::list<std::string>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << it->c_str() << "\n";
	}


	while (!GraphicEngine::GetInstance()->ShouldCloseMainWindow())
	{

		//option to reset the simultation
		if (GraphicEngine::GetInstance()->shouldReset())
		{
			GraphicEngine::GetInstance()->setReset(false);

			DeleteObject();
			DeleteObjectForce();
			if (GraphicEngine::GetInstance()->isForce())
			{
				SetupObject();
			}
			else
			{
				SetupObjectForce();
			}
		}

		//tick the system
		MainEngine::GetInstance()->Tick();
		//std::cout << ((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT() << "\n";

		
		if (!GraphicEngine::GetInstance()->isPaused())
		{
			//Physic
			PhysicEngine::GetInstance()->Integrade(((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT());

			MainEngine::GetInstance()->UpdateEntityPostion();
		}
		//Graphic
		GraphicEngine::GetInstance()->Display();


	}


	GraphicEngine::GetInstance()->Delete();
	delete(GraphicEngine::GetInstance());


	return 0;

}