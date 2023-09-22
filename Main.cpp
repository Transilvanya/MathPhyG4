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



const unsigned int width = 1600;
const unsigned int height = 800;



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




Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


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
	//Setup OpeGL

	const char* glsl_version = "#version 130";
	GLFWwindow* window;
	try
	{
		window = Manager::InitWindow(width, height);
	}
	catch (InitException e)
	{
		std::cout << "InitWindow failed" << std::endl;
		return -1;
	}

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("OpenGL/Shaders/simplecolor.vert", "OpenGL/Shaders/simplecolor.frag");
	Shader shaderProgram2("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");


	//create a 3D object to display
	ThreeDObject Obj(shaderProgram, indicevector, verticevector);

	//Obj.AddIndice(2);
	//Obj.AddIndice(3);
	//Obj.AddIndice(6);

	//Obj.Update();


	Obj.SetIndice(9, 1);
	Obj.SetIndice(10, 2);
	Obj.SetIndice(11, 5);

	Obj.Update();



	// Texture ______________________________________

	//Create the path to a texture
	std::string parentDir = fs::current_path().string();
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/BasicGraphicEngine/";
	
	// Create a texture
	Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//Create a 3Dobject with a texture
	ThreeDObjectTexture Obj2(shaderProgram2, brickTex, indicevector2, verticevector2);
	Obj2.Update();


	
	Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	ThreeDObjectTexture Obj3(shaderProgram2, catTex, indicevector3, verticevector3);
	Obj3.Update();


	// ______________________________     ImGui Setup
	

	ImGuiIO& io = ImGuiSetup(window, glsl_version);
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// keybind controler_________________________________


	setAfunc(cameraMoveLeft);
	setDfunc(cameraMoveRight);
	setWfunc(cameraMoveFoward);
	setSfunc(cameraMoveBackward);

	setSpacefunc(cameraMoveUp);
	setLeftCtrlfunc(cameraMoveDown);

	setMousePosfunc(cameraRotation);


	setMouseReleasefunc(cameraSettoDrift);


	float x = 0.5f;
	float y = 0.5f;

	while (!Manager::CloseMainWindow(window))
	{
		//Obj2.SetMvt(0.1f, 0.0f, 0.0f);
		//Obj2.Update();

		
		// ____ imgui
		 
		//Create a new frame
		NewFrame();

		//Collect inputs
		InputControler();

		//create a ImGui window
		BasicWindowsDisplay(show_demo_window, show_another_window, clear_color, io);



		

		// show camera rotation with a debug window
		x = acos(camera.GetRotationDrift().z);
		if (asin(camera.GetRotationDrift().x) < 0)
			x = x * -1;
		if (!(x >= -3.2f && x <= 3.2f))
			x = 0.0f;
		y = camera.GetRotationDrift().y;

		ImGui::SliderFloat("slider float", &x, -3.14f, 3.14f, "%.2f");

		ImGui::VSliderFloat("##v", ImVec2(28, 160), &y, -1.0f, 1.0f, "%.1f");
		//ImGui::PopID();
		//camera.SetRotation(glm::vec3(sin(x), y, cos(x)));
		// ---------



		//render Imgui
		RenderFrame();


		
		Manager::ClearBGColor();


		//Obj.Draw(camera);
		Obj3.Draw(camera);

		//Render the 3D objects
		RenderFrameData();

		Manager::CleanElements(window);
	}



	// Cleanup
	CleanUp();

	// Delete all the objects we've created
	//VAO1.Delete();
	//VBO1.Delete();
	//EBO1.Delete();


	brickTex.Delete();

	shaderProgram.Delete();
	shaderProgram2.Delete();


	Manager::DeleteWindow(window);

	return 0;
}