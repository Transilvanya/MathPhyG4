




#include "MainEngine/MainEngine.h"
#include "PhysicEngine/PhysicEngine.h"
#include "GraphicEngine/GraphicEngine.h"
#include "PhysicEngine/Matrices/Matrice34.h"

/* -- static init -- */

MainEngine* MainEngine::_mainmanagerptr = NULL;
PhysicEngine* PhysicEngine::_physicengineptr = NULL;
GraphicEngine* GraphicEngine::_graphicengineptr = NULL;

/* -- ----------- -- */

/*


*/


void SetupObject()
{
	std::vector<GLfloat> CubeVertex =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-2.0f, 0.0f, -2.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		-2.0f, 0.0f,  2.0f,	0.83f, 0.70f, 0.44f,	0, 10,
		 2.0f, 0.0f,  2.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 2.0f, 0.0f, -2.0f,   0.83f, 0.70f, 0.44f,	10, 0,

		-2.0f, 1.0f, -2.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		-2.0f, 1.0f,  2.0f,	 0.83f, 0.70f, 0.44f,	0, 10,
		 2.0f, 1.0f,  2.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 2.0f, 1.0f, -2.0f,   0.83f, 0.70f, 0.44f,	10, 0,
	};
	std::vector<GLuint> CubeIndice =
	{
		0, 1, 2,
		0, 2, 3,

		4,5,6,
		4,6,7,

		0,4,5,
		0,5,1,

		6,5,1,
		6,1,2,

		7,6,2,
		7,2,3,

		4,7,0,
		7,0,3,
	};

	std::vector<GLfloat> CylinderVertex =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-1.0f, 0.0f,  0.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		 1.0f, 0.0f,  0.0f,		0.83f, 0.70f, 0.44f,	0, 10,
		 0.0f, 0.0f,  1.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 0.0f, 0.0f, -1.0f,   0.83f, 0.70f, 0.44f,	10, 0,

		-1.0f, 3.0f,  0.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		 1.0f, 3.0f,  0.0f,	 0.83f, 0.70f, 0.44f,	0, 10,
		 0.0f, 3.0f,  1.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 0.0f, 3.0f, -1.0f,   0.83f, 0.70f, 0.44f,	10, 0,
	};
	std::vector<GLuint> CylinderIndice =
	{
		0,1,2,
		0,1,3,

		4,5,6,
		4,5,7,

		0,3,4,
		4,7,3,

		1,3,7,
		7,5,1,

		1,2,5,
		5,6,2,

		0,2,6,
		6,4,0,
	};

	GraphicEngine::GetInstance()->CreateSphereText("sphere", "simpletext", "cattext", 0.6f);
	GraphicEngine::GetInstance()->CreatePolygonText("cuboid", "simpletext", "brick", CubeIndice, CubeVertex, 0, 0, 0);
	GraphicEngine::GetInstance()->CreatePolygonText("polygon", "simpletext", "cattext", CylinderIndice, CylinderVertex, 0, 0, 0);


	PhysicEngine::GetInstance()->CreateRigidSphere(1, 100, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0),Quaternion(0,1,0,0), Vector3D(1, 1, 0), Vector3D(0, 0, 0), "sphereRB");
	PhysicEngine::GetInstance()->CreateRigidCuboid(2, 1, 2, 100, Vector3D(0, 3, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 0), Quaternion(1, 0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), "cuboidRB");
	PhysicEngine::GetInstance()->CreateRigidCylinder(1, 3, 100, Vector3D(3, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Quaternion(1, 1, 0, 0), Vector3D(0, 0, 1), Vector3D(0, 0, 0), "polygonRB");





	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("sphereRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("sphere"), "entity1");
	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("cuboidRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("cuboid"), "entity2");
	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("polygonRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("polygon"), "entity3");



}


void SetupObject2()
{
	std::vector<GLfloat> CubeVertex =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-2.0f, -0.5f, -2.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		-2.0f, -0.5f,  2.0f,	0.83f, 0.70f, 0.44f,	0, 10,
		 2.0f, -0.5f,  2.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 2.0f, -0.5f, -2.0f,   0.83f, 0.70f, 0.44f,	10, 0,

		-2.0f, 0.5f, -2.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		-2.0f, 0.5f,  2.0f,	 0.83f, 0.70f, 0.44f,	0, 10,
		 2.0f, 0.5f,  2.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 2.0f, 0.5f, -2.0f,   0.83f, 0.70f, 0.44f,	10, 0,
	};
	std::vector<GLuint> CubeIndice =
	{
		0, 1, 2,
		0, 2, 3,

		4,5,6,
		4,6,7,

		0,4,5,
		0,5,1,

		6,5,1,
		6,1,2,

		7,6,2,
		7,2,3,

		4,7,0,
		7,0,3,
	};

	std::vector<GLfloat> CylinderVertex =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-1.0f, -1.5f,  0.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		 1.0f, -1.5f,  0.0f,		0.83f, 0.70f, 0.44f,	0, 10,
		 0.0f, -1.5f,  1.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 0.0f, -1.5f, -1.0f,   0.83f, 0.70f, 0.44f,	10, 0,

		-1.0f, 1.5f,  0.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		 1.0f, 1.5f,  0.0f,	 0.83f, 0.70f, 0.44f,	0, 10,
		 0.0f, 1.5f,  1.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 0.0f, 1.5f, -1.0f,   0.83f, 0.70f, 0.44f,	10, 0,
	};
	std::vector<GLuint> CylinderIndice =
	{
		0,1,2,
		0,1,3,

		4,5,6,
		4,5,7,

		0,3,4,
		4,7,3,

		1,3,7,
		7,5,1,

		1,2,5,
		5,6,2,

		0,2,6,
		6,4,0,
	};

	GraphicEngine::GetInstance()->CreateSphereText("sphere", "simpletext", "cattext", 0.6f);
	GraphicEngine::GetInstance()->CreatePolygonText("cuboid", "simpletext", "cattext", CubeIndice, CubeVertex, 0, 0, 0);
	GraphicEngine::GetInstance()->CreatePolygonText("polygon", "simpletext", "cattext", CylinderIndice, CylinderVertex, 0, 0, 0);


	PhysicEngine::GetInstance()->CreateRigidSphere(1, 100, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Quaternion(0, 1, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), "sphereRB");
	PhysicEngine::GetInstance()->CreateRigidCuboid(2, 1, 2, 100, Vector3D(0, 3, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Quaternion(1, 0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), "cuboidRB");
	PhysicEngine::GetInstance()->CreateRigidCylinder(1, 3, 100, Vector3D(3, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Quaternion(1, 1, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), "polygonRB");





	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("sphereRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("sphere"), "entity1");
	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("cuboidRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("cuboid"), "entity2");
	MainEngine::GetInstance()->CreateEntityRB(PhysicEngine::GetInstance()->GetRigidBody("polygonRB"), GraphicEngine::GetInstance()->GetObjectwithTexture("polygon"), "entity3");



}



void DeleteObject()
{
	MainEngine::GetInstance()->RemoveEntityRB("entity1");
	GraphicEngine::GetInstance()->RemoveGraphicObject("sphere");
	PhysicEngine::GetInstance()->RemoveRigidBody("sphereRB");

	MainEngine::GetInstance()->RemoveEntityRB("entity2");
	GraphicEngine::GetInstance()->RemoveGraphicObject("cuboid");
	PhysicEngine::GetInstance()->RemoveRigidBody("cuboidRB");

	MainEngine::GetInstance()->RemoveEntityRB("entity3");
	GraphicEngine::GetInstance()->RemoveGraphicObject("polygon");
	PhysicEngine::GetInstance()->RemoveRigidBody("polygonRB");

}

/*

void SetupObject()
{
	GraphicEngine::GetInstance()->CreateSphereText("sphere3", "simpletext", "cattext", 0.6f, 5, 0, 0);
	GraphicEngine::GetInstance()->CreateSphereText("sphere7", "simpletext", "cattext", 0.6f, 5, 10, 0);

	GraphicEngine::GetInstance()->CreateSphereText("sphere4", "simpletext", "cattext", 0.6f, 0, 5, 0);
	GraphicEngine::GetInstance()->CreateSphereText("sphere6", "simpletext", "brick", 0.6f, 5, 5, 0);
	GraphicEngine::GetInstance()->CreateSphereText("sphere5", "simpletext", "cattext", 0.6f, 10, 5, 0);



	PhysicEngine::GetInstance()->CreateParticule(Vector3D(5, 0, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 0), 200, "particule3");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(5, 10, 0), Vector3D(0, -1, 0), Vector3D(0, 0, 0), 100, "particule7");


	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 5, 0), Vector3D(1, 0, 0), Vector3D(0, 0, 0), 100, "particule4");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(5, 5, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 100, "particule6");
	PhysicEngine::GetInstance()->CreateParticule(Vector3D(10, 5, 0), Vector3D(-2, 0, 0), Vector3D(0, 0, 0), 100, "particule5");


	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule3"), GraphicEngine::GetInstance()->GetGraphicObject("sphere3"), "entity3");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule7"), GraphicEngine::GetInstance()->GetGraphicObject("sphere7"), "entity7");

	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule4"), GraphicEngine::GetInstance()->GetGraphicObject("sphere4"), "entity4");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule6"), GraphicEngine::GetInstance()->GetGraphicObject("sphere6"), "entity6");
	MainEngine::GetInstance()->CreateEntity(PhysicEngine::GetInstance()->GetParticule("particule5"), GraphicEngine::GetInstance()->GetGraphicObject("sphere5"), "entity5");




	PhysicEngine::GetInstance()->GetContactRegistry()->CreateRod(PhysicEngine::GetInstance()->GetParticule("particule6"), PhysicEngine::GetInstance()->GetParticule("particule4"), "link2", 5, false);
	PhysicEngine::GetInstance()->GetContactRegistry()->CreateRod(PhysicEngine::GetInstance()->GetParticule("particule5"), PhysicEngine::GetInstance()->GetParticule("particule6"), "link1", 5, true);

	PhysicEngine::GetInstance()->GetContactRegistry()->CreateAnchor(PhysicEngine::GetInstance()->GetParticule("particule5"), Vector3D(10, 6, 0), "anchor1", 1, false);
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

	PhysicEngine::GetInstance()->GetContactRegistry()->RemoveLink("link1");
	PhysicEngine::GetInstance()->GetContactRegistry()->RemoveLink("link2");

	PhysicEngine::GetInstance()->GetContactRegistry()->RemoveAnchor("anchor1");
}
//

void SetupObjectForce()
{
	GraphicEngine::GetInstance()->CreateSphereText("sphere", "simpletext", "cattext", 0.5f, 0, 3, 0);
	GraphicEngine::GetInstance()->CreateSphereText("sphere2", "simpletext", "cattext", 0.5f, 10, 0, 0);
	GraphicEngine::GetInstance()->CreateSphereText("sphere3", "simpletext", "cattext", 0.5f, -10, 0, 0);


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

	std::vector<GLfloat> groundvertice2 =
	{  //     COORDINATES     /        COLORS      /   TexCoord  //
		-20.0f, 0.0f, -20.0f,   0.83f, 0.70f, 0.44f,	0, 0,
		- 20.0f, 0.0f,  20.0f,	0.83f, 0.70f, 0.44f,	0, 10,
		 20.0f, 0.0f,  20.0f,   0.83f, 0.70f, 0.44f,	10, 10,
		 20.0f, 0.0f, -20.0f,   0.83f, 0.70f, 0.44f,	10, 0,
	};
	std::vector<GLuint> groundindice2 =
	{
		0, 1, 2,
		0, 2, 3,
	};


	GraphicEngine::GetInstance()->CreateShader("simplecolor", "GraphicEngine/OpenGL/Shaders/simplecolor.vert", "GraphicEngine/OpenGL/Shaders/simplecolor.frag");
	GraphicEngine::GetInstance()->CreateShader("simpletext", "GraphicEngine/OpenGL/Shaders/simpletext.vert", "GraphicEngine/OpenGL/Shaders/simpletext.frag");

	GraphicEngine::GetInstance()->CreateTexture("cattext", "border.png");
	GraphicEngine::GetInstance()->CreateTexture("brick", "brick.png");

	//GraphicEngine::GetInstance()->CreatePolygon("newobject", "simplecolor", groundindice, groundvertice);

	GraphicEngine::GetInstance()->CreatePolygonText("newobject2", "simpletext", "brick", groundindice2, groundvertice2, 0,0,0);


	SetupObject();







	std::list<std::string> lst = MainEngine::GetInstance()->GetEntities();

	std::list<std::string>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << it->c_str() << "\n";
	}

	while (!GraphicEngine::GetInstance()->ShouldCloseMainWindow())
	{
		//GraphicEngine::GetInstance()->GetPolygonText("newobject2")->SetMvt(0, 0.01f, 0);
		//GraphicEngine::GetInstance()->GetPolygonText("newobject2")->AddRot(0.0f, 0.01f, 0.001f);
		GraphicEngine::GetInstance()->GetPolygonText("newobject2")->ElementToUpdate();

		//option to reset the simultation
		if (GraphicEngine::GetInstance()->shouldReset())
		{
			GraphicEngine::GetInstance()->setReset(false);

			DeleteObject();
			if (GraphicEngine::GetInstance()->Bool1())
			{
				SetupObject();
			}
			else if (GraphicEngine::GetInstance()->Bool2())
			{
				SetupObject2();
			}
			else if(GraphicEngine::GetInstance()->Bool4())
			{

			}
			else if(GraphicEngine::GetInstance()->Bool4())
			{

			}
			else if(GraphicEngine::GetInstance()->Bool5())
			{

			}
			else
			{

			}
		}

		//tick the system
		MainEngine::GetInstance()->Tick();
		//std::cout << ((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT() << "\n";

		
		if (!GraphicEngine::GetInstance()->isPaused())
		{

			//PhysicEngine::GetInstance()->GetRigidBody("sphereRB")->AddForce(Vector3D(0,100,0));
			//PhysicEngine::GetInstance()->GetRigidBody("sphereRB")->AddForceAtBodyPoint(Vector3D(0, 10, 0), Vector3D(1, 0, 0));
			//PhysicEngine::GetInstance()->GetRigidBody("sphereRB")->AddForcePoint(Vector3D(0, 10, 0), Vector3D(1, 0, 0));

			//PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForcePoint(Vector3D(0, 100, 0), Vector3D(1, 0, 0));
			//PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForcePoint(Vector3D(0, 100, 0), Vector3D(-1, 0, 0));
//			PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForceAtBodyPoint(Vector3D(0, 100, 0), Vector3D(3, 0, 0));
//			PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForcePoint(Vector3D(0, -100, 0), Vector3D(-3, 0, 0));

			
			PhysicEngine::GetInstance()->GetRigidBody("polygonRB")->AddForcePoint(Vector3D(0, 3, 0), Vector3D(3, 0, 0));
			PhysicEngine::GetInstance()->GetRigidBody("polygonRB")->AddForcePoint(Vector3D(0, -3, 0), Vector3D(-3, 0, 0));

			PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForcePoint(Vector3D(0, 10, 0), Vector3D(3, 0, 0));
			PhysicEngine::GetInstance()->GetRigidBody("cuboidRB")->AddForcePoint(Vector3D(0, -10, 0), Vector3D(-3, 0, 0));


			PhysicEngine::GetInstance()->GetRigidBody("sphereRB")->AddForceAtBodyPoint(Vector3D(0, 10, 0), Vector3D(3, 0, 0));
			PhysicEngine::GetInstance()->GetRigidBody("sphereRB")->AddForceAtBodyPoint(Vector3D(0, -10, 0), Vector3D(-3, 0, 0));

			//Physic
			PhysicEngine::GetInstance()->Integrade(((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT()* GraphicEngine::GetInstance()->GetSimulationSpeed());

			MainEngine::GetInstance()->UpdateEntityPostion();
		}
		//Graphic
		GraphicEngine::GetInstance()->Display();


	}


	GraphicEngine::GetInstance()->Delete();
	delete(GraphicEngine::GetInstance());


	return 0;

}