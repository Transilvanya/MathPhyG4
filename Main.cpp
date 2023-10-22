




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

	GraphicEngine::GetInstance()->CreateSphere("sphere", "simplecolor", 1, 0, 0, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere2", "simplecolor", 1, 0.5f, 0, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere3", "simplecolor", 1, -0.5f, 0, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere4", "simplecolor", 1, 2, 0, 0, 1, 1, 1, 1);

	GraphicEngine::GetInstance()->CreateSphere("sphere5", "simplecolor", 1, 10, 6, 0, 1, 1, 1, 1);
	GraphicEngine::GetInstance()->CreateSphere("sphere6", "simplecolor", 1, 0, 5, 0, 1, 1, 1, 1);

	GraphicEngine::GetInstance()->CreateSphere("sphere7", "simplecolor", 1, -10, 1, 0, 1, 1, 1, 1);

	/*
	MainEngine::GetInstance()->Init();
	MainEngine::GetInstance()->ElementToUpdate();
	TimeSystem* ts = (TimeSystem*) MainEngine::GetInstance()->GetSystem("timesystem");
	*/


	std::vector<GLfloat> circlev =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //


		0.0f, 1.0f, 3.155f,   0.43f, 0.70f, 0.84f,	1.0f,

		0.5f, 1.0f, 0.0f,		0.83f, 0.70f, 0.44f,	1.0f,
		1.45f, 1.0f, 0.31f,		0.83f, 0.70f, 0.44f,	1.0f,
		2.26f, 1.0f, 0.9f,		0.83f, 0.70f, 0.44f,	1.0f,
		2.85f, 1.0f, 1.71f ,	0.83f, 0.70f, 0.44f,	1.0f,
		3.16f, 1.0f, 2.66f ,	0.83f, 0.70f, 0.44f,	1.0f,
		3.16f, 1.0f ,3.66f ,	0.83f, 0.70f, 0.44f,	1.0f,
		2.85f, 1.0f, 4.61f ,	0.83f, 0.70f, 0.44f,	1.0f,
		2.26f, 1.0f, 5.42f ,	0.83f, 0.70f, 0.44f,	1.0f,
		1.45f, 1.0f, 6.0f ,		0.83f, 0.70f, 0.44f,	1.0f,
		0.5f, 1.0f, 6.31f ,		0.83f, 0.70f, 0.44f,	1.0f,

		-0.5f, 1.0f, 6.31f ,	0.83f, 0.70f, 0.44f,	1.0f,
		-1.45f, 1.0f, 6.0f ,	0.83f, 0.70f, 0.44f,	1.0f,
		-2.26f, 1.0f, 5.42f ,	0.83f, 0.70f, 0.44f,	1.0f,
		-2.85f, 1.0f, 4.61f ,   0.83f, 0.70f, 0.44f,	1.0f,
		-3.16f, 1.0f ,3.66f ,   0.83f, 0.70f, 0.44f,	1.0f,
		-3.16f, 1.0f, 2.66f ,   0.83f, 0.70f, 0.44f,	1.0f,
		-2.85f, 1.0f, 1.71f ,   0.83f, 0.70f, 0.44f,	1.0f,
		-2.26f, 1.0f, 0.9f ,	0.83f, 0.70f, 0.44f,	1.0f,
		-1.45f, 1.0f, 0.31f ,   0.83f, 0.70f, 0.44f,	1.0f,
		-0.5f, 1.0f, 0.0f ,		0.83f, 0.70f, 0.44f,	1.0f,


	};
	std::vector<GLuint> circlei =
	{

		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 11,
		0, 11, 12,
		0, 12, 13,
		0, 13, 14,
		0, 14, 15,
		0, 15, 16,
		0, 16, 17,
		0, 17, 18,
		0, 18, 19,
		0, 19, 20,
		0, 20, 1,

	};

	GraphicEngine::GetInstance()->CreatePolygon("circle", "simplecolor", circlei, circlev);



	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 10, "particule");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0.5f, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 100, "particule2");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(-0.5f, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 200, "particule3");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(2, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 50, "particule4");

	PhysicEngine::GetInstance()->CreateParticule(Vector3D(10, 6, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 50, "particule5");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 5, 0), Vector3D(10, 0, 0), Vector3D(0, 0, 0), 100, "particule6");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(-10, 1, 0), Vector3D(11, 0, 0), Vector3D(0, 0, 0), 100, "particule7");


	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule"), GraphicEngine::GetInstance()->GetGraphicObject("sphere"), "entity1");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule2"), GraphicEngine::GetInstance()->GetGraphicObject("sphere2"), "entity2");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule3"), GraphicEngine::GetInstance()->GetGraphicObject("sphere3"), "entity3");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule4"), GraphicEngine::GetInstance()->GetGraphicObject("sphere4"), "entity4");

	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule5"), GraphicEngine::GetInstance()->GetGraphicObject("sphere5"), "entity5");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule6"), GraphicEngine::GetInstance()->GetGraphicObject("sphere6"), "entity6");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule7"), GraphicEngine::GetInstance()->GetGraphicObject("sphere7"), "entity7");





	std::list<std::string> lst = MainEngine::GetInstance()->GetEntities();

	std::list<std::string>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << it->c_str() << "\n";
	}


	while (!GraphicEngine::GetInstance()->ShouldCloseMainWindow())
	{
		MainEngine::GetInstance()->Tick();


		//std::cout << ((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT() << "\n";

		//Physic
		PhysicEngine::GetInstance()->Integrade(((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT());

		MainEngine::GetInstance()->UpdateEntityPostion();

		//Graphic
		GraphicEngine::GetInstance()->Display();


	}


	GraphicEngine::GetInstance()->Delete();
	delete(GraphicEngine::GetInstance());


	return 0;

}