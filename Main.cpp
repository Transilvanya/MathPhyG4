//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"OpenGL/Texture.h"
#include"OpenGL/shaderClass.h"
#include"OpenGL/VAO.h"
#include"OpenGL/VBO.h"
#include"OpenGL/EBO.h"
#include"OpenGL/Camera.h"






#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif


#include "MainManager/MainEngine.h"
#include "PhysicEngine/PhysicEngine.h"
#include "GraphicEngine/GraphicEngine.h"





/* -- static init -- */

MainEngine* MainEngine::_mainmanagerptr = NULL;
PhysicEngine* PhysicEngine::_physicengineptr = NULL;
GraphicEngine* GraphicEngine::_graphicengineptr = NULL;

/* -- ----------- -- */


const unsigned int width = 1600;
const unsigned int height = 800;

/*

std::vector<GLfloat> verticevector =
{ //     COORDINATES     /        COLORS      /   Alpha  //
	-0.5f, 0.0f,  0.5f,     0.13f, 0.10f, 0.94f,	1.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f,
	 0.7f, 0.0f,  0.5f,     0.03f, 0.00f, 0.44f,	0.1f,
	 0.0f, 0.8f,  0.0f,     0.12f, 0.86f, 0.16f,	1.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.06f, 0.16f,	1.0f,
	 0.0f, 0.8f,  0.0f,     0.12f, 0.06f, 0.96f,	1.0f,
};

std::vector<GLfloat> verticevector2 =
{  //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.9f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};


std::vector<GLfloat> verticevector3 =
{  //     COORDINATES     /        COLORS      /   TexCoord  //
	 0.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.0f, 0.0f,  1.0f,		0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 1.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 1.0f, 0.0f,  0.0f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 1.0f, 1.0f,  0.0f,		0.83f, 0.70f, 0.44f,	0.0f, 2.0f,
	 1.0f, 1.0f,  1.0f,     0.83f, 0.70f, 0.44f,	2.0f, 2.0f,
	 1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	2.0f, 0.0f,
};

std::vector<GLuint> indicevector3 = {
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

};

std::vector<GLuint> indicevector2 = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

std::vector<GLuint> indicevector =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	3, 0, 4
};

*/

std::vector<GLfloat> backgroundvertice =
{  //     COORDINATES     /        COLORS      /   TexCoord  //
	-20.0f,  0.0f,  -20.0f,   0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-20.0f, 20.0f,  -20.0f,	 0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
	 20.0f, 20.0f,  -20.0f,   0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 20.0f,  0.0f,  -20.0f,   0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
};
std::vector<GLuint> backgroundindice =
{
	0, 1, 2,
	0, 2, 3,
};

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

std::vector<GLfloat> Forcevertice =
{  //     COORDINATES     /        COLORS      /   Alpha  //
	-0.1f,		0.0f,	0.0f,     0.13f, 0.10f, 0.94f,	1.0f,
	0.1f,		0.0f,	0.0f,		0.13f, 0.10f, 0.94f,	1.0f,
	0.0f,		-0.1f,	0.0f,		0.13f, 0.10f, 0.94f,	1.0f,
	0.0f,		0.1f,	0.0f,		0.13f, 0.10f, 0.94f,	1.0f,
	0.0f,		0.0f,	-0.1f,		0.13f, 0.10f, 0.94f,	1.0f,
	0.0f,		0.0f,	0.1f,		0.13f, 0.10f, 0.94f,	1.0f,
};
std::vector<GLuint> Forceindice =
{
	3,1,5,
	1,2,5,
	0,2,5,
	0,3,5,
	3,1,4,
	1,2,4,
	0,2,4,
	0,3,4
};

Camera camera(width, height, glm::vec3(0.0f, 1.0f, 20.0f));


//function to bind to the InputControler

void cameraMoveLeft()
{
	camera.MoveLeftCamera();
}
void cameraMoveRight()
{
	camera.MoveRightCamera();
}
void cameraMoveFoward()
{
	camera.MoveFowardCamera();
}
void cameraMoveBackward()
{
	camera.MoveBackwardCamera();
}
void cameraMoveUp()
{
	camera.MoveUpCamera();
}
void cameraMoveDown()
{
	camera.MoveDownCamera();
}
void cameraRotation(int _xpos, int _ypos)
{
	if (_xpos < width / 10 || _xpos > width * 9 / 10)
	{
	//	camera.RotateCamera(_xpos, _ypos );
	}
	if (_ypos < height / 10 || _ypos > height * 9 / 10)
	{
		
	}
camera.RotateCamera(_xpos, _ypos);
	
}
void cameraSettoDrift()
{
	camera.SetCameraToDrift();
}

int main()
{
	PhysicEngine::GetInstance()->Init();

	MainEngine::GetInstance()->Init();


	PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, 0, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 0), 1, "particule1");
	//PhysicEngine::GetInstance()->CreateParticule(Vector3D(0, -2, 0), Vector3D(0, 0, 0.1f), Vector3D(0, 0, 0), 100, "particule2");

	PhysicEngine::GetInstance()->GetForceRegistry()->AddForceGravityToParticule(PhysicEngine::GetInstance()->GetParticule("particule1"), "gravity1");
	//PhysicEngine::GetInstance()->GetForceRegistry()->RemoveForceFromParticule("particule2", "buoyancy1");
	//PhysicEngine::GetInstance()->RemoveParticule("particule2");

	int i = 0;
	while (i < 100)
	{
		i++;
		MainEngine::GetInstance()->Tick();

		PhysicEngine::GetInstance()->Integrade(((TimeSystem*)MainEngine::GetInstance()->GetSystem("TimeSystem"))->GetDeltaT());

		//Sync the position of the graphic object and the physic object
		//to do after graphic engine
		MainEngine::GetInstance()->UpdateEntityPostion();

		//GraphicEngine::GetInstance()->Display();
	}

	return 0;
}