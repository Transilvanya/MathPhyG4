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

#include "UI/imgui_perso.cpp"
#include "UI/InputControler.cpp"
#include "OpenGL/Manager.h"
#include "UI/ImGuiOpenGLManager.cpp"
#include "UI/Windows/BasicWindows.cpp"
#include "OpenGL/ThreeDObject.h"
#include "OpenGL/ParticuleObject.h"
#include "Particules/Particules.h"
#include "MainManager/MainManager.h"
#include "PhysicEngine/PhysicEngine.h"
#include "GraphicEngine/GraphicEngine.h"




/* -- static init -- */

MainManager* MainManager::_mainmanagerptr = NULL;
PhysicEngine* PhysicEngine::_physicengineptr = NULL;
GraphicEngine* GraphicEngine::_graphicengineptr = NULL;

/* -- ----------- -- */



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







int main()
{

	




	MainManager::GetInstance()->Init();
	MainManager::GetInstance()->Update();
	//TimeSystem* ts = (TimeSystem*) MainManager::GetInstance()->GetSystem("timesystem");

	GraphicEngine::GetInstance()->init();
	
	
	Entity* e = new Entity(new PhysicObject(), new GraphicObject(0.0f, 0.0f, 0.f, 1.f, 1.f, 1.f, 0.f, 2.f), "name");
	e->SetName("name");

	//MainManager::GetInstance()->AddEntity(e);

	//MainManager::GetInstance()->RemoveSystem("timesystem");
	//MainManager::GetInstance()->RemoveEntity("name");

	//if (MainManager::GetInstance()->GetEntity("name") != nullptr)
	//{
	//	std::cout << "success\n";
	//}
	//else
	//{
	//	std::cout << "failed\n";
	//}
	


	return EXIT_SUCCESS;
}