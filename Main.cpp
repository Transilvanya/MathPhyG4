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
	Shader shaderProgramColor("OpenGL/Shaders/simplecolor.vert", "OpenGL/Shaders/simplecolor.frag");
	Shader shaderProgramTextureBG("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");
	Shader shaderProgramTextureGround("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");

	
	//create a 3D object to display
	ThreeDObject ForceObj(shaderProgramColor, Forceindice, Forcevertice);

	


	// Texture ______________________________________

	//Create the path to a texture
	std::string parentDir = fs::current_path().string();
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/BasicGraphicEngine/";
	
	// Create a texture
	Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//Create a 3Dobject with a texture
	ThreeDObject GroundObj(shaderProgramColor, groundindice, groundvertice);
	
	Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	ThreeDObjectTexture BGObj(shaderProgramTextureBG, catTex, backgroundindice, backgroundvertice);



	ParticuleObject ParticuleObject(0.0f, 0.0f , -18.0f ,0.9f, 0.0f, 0.5f, 1.0f, 1.0f);
	
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

	Particules particule1(Vector3D(0.0f, 0.0f, -18.0f), Vector3D(5.0f, 20.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f));

	Vector3D gravity(0.0f, -9.8f, 0.0f);
	Vector3D NoForce(0.0f, 0.0f, 0.0f);

	particule1.setForce(gravity * particule1.getMasse());

	float FrameRate = 1.0f / 60.0f;

	bool ParticuleContact = false;

	float prevx = particule1.getPostion().getX();
	float prevy = particule1.getPostion().getY();
	float prevz = particule1.getPostion().getZ();


	Vector3D UserForce(0, 0, 0);
	
	static bool Paused = false;
	static bool UserForceEnabled = true;

	while (!Manager::CloseMainWindow(window) )
	{
		if (!Paused)
		{

			particule1.intergrade(FrameRate);


			if ((particule1.getForce()+ UserForce).getX() < 0)
			{
				ForceObj.SetValue(0, (particule1.getForce() + UserForce).getX());
				ForceObj.SetValue(7, 0.1f);
			}
			else
			{
				ForceObj.SetValue(0, -0.1f);
				ForceObj.SetValue(7, (particule1.getForce() + UserForce).getX());
			}
			if (particule1.getForce().getY() < 0)
			{
				ForceObj.SetValue(1+14, (particule1.getForce() + UserForce).getY());
				ForceObj.SetValue(1+21, 0.1f);
			}
			else
			{
				ForceObj.SetValue(1+14, -0.1f);
				ForceObj.SetValue(1+21, (particule1.getForce() + UserForce).getY());
			}
			if (particule1.getForce().getZ() < 0)
			{
				ForceObj.SetValue(2+28, (particule1.getForce() + UserForce).getZ());
				ForceObj.SetValue(2+35, 0.1f);
			}
			else
			{
				ForceObj.SetValue(2+28, -0.1f);
				ForceObj.SetValue(2+35, (particule1.getForce() + UserForce).getZ());
			}
			ForceObj.Update();

			ParticuleObject.SetMvt(particule1.getPostion().getX() - prevx, particule1.getPostion().getY() - prevy, particule1.getPostion().getZ() - prevz);
			ParticuleObject.Update();

			prevx = particule1.getPostion().getX();
			prevy = particule1.getPostion().getY();
			prevz = particule1.getPostion().getZ();

			if (particule1.getPostion().getY() <= 0.01f)
			{
				float tempx = particule1.getVitesse().getX();
				float tempy = particule1.getVitesse().getY();
				float tempz = particule1.getVitesse().getZ();

				particule1.setForce(UserForce + Vector3D(-tempx * abs(tempx), -tempy * abs(tempy), -tempz * abs(tempz)));

			}
			else
			{
				particule1.setForce(UserForce + gravity * particule1.getMasse());
			}
		}
		//std::cout << particule1.getPostion().getX() << "\t" << particule1.getPostion().getY() << "\t" << particule1.getPostion().getZ() << "\n";
		
		
		//Obj2.SetMvt(0.1f, 0.0f, 0.0f);
		//Obj2.Update();

		
		// ____ imgui
		 
		//Create a new frame
		NewFrame();

		//Collect inputs
		InputControler();

		//create a ImGui window
		//BasicWindowsDisplay(show_demo_window, show_another_window, clear_color, io);



		ImGui::Begin("Debug");
		if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::SeparatorText("ABOUT THIS DEMO:");
			ImGui::BulletText("Camera controls : ZQSD (qwerty), WASD (azerty),\n crtl to go down, space to go up, mouse left click to orient the camera.");
			ImGui::BulletText("The rotation of the camera will be fixed at the center\n of the screen but will keep rotation we the mouse reach the edges.");
			ImGui::BulletText("The blue shape indicape the forces applied to the particule");
		}

		if (ImGui::Button("Reset"))
		{
			particule1 = Particules(Vector3D(0.0f, 0.0f, -18.0f), Vector3D(5.0f, 20.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f));

			particule1.setForce(gravity * particule1.getMasse());
		}

		// show camera rotation with a debug window
		x = acos(camera.GetRotationDrift().z);
		if (asin(camera.GetRotationDrift().x) < 0)
			x = x * -1;
		if (!(x >= -3.2f && x <= 3.2f))
			x = 0.0f;
		y = camera.GetRotationDrift().y;

		ImGui::SliderFloat(" ", &x, -3.14f, 3.14f, "%.2f");
		ImGui::SetItemTooltip("Horizontal Camera Orientation");

		ImGui::VSliderFloat("##v", ImVec2(28, 160), &y, -1.0f, 1.0f, "%.1f");
		ImGui::SetItemTooltip("Vertical Camera Orientation");
		//ImGui::PopID();
		//camera.SetRotation(glm::vec3(sin(x), y, cos(x)));
		// ---------


		ImGui::Text("position     = %.1f \t%.1f \t%.1f", particule1.getPostion().getX(), particule1.getPostion().getY(), particule1.getPostion().getZ());
		ImGui::Text("vitesse      = %.1f \t%.1f \t%.1f", particule1.getVitesse().getX(), particule1.getVitesse().getY(), particule1.getVitesse().getZ());
		ImGui::Text("acceleration = %.1f \t%.1f \t%.1f", particule1.getAcceleration().getX(), particule1.getAcceleration().getY(), particule1.getAcceleration().getZ());

		ImGui::SeparatorText("User defined force");

		static float f1 = 0.001f;
		ImGui::InputFloat("input x", &f1, 0.01f, 1.0f, "%.3f");
		ImGui::SetItemTooltip("X Component of the force applied to the particule");

		static float f2 = 0.001f;
		ImGui::InputFloat("input y", &f2, 0.01f, 1.0f, "%.3f");
		ImGui::SetItemTooltip("Y Component of the force applied to the particule");
		
		static float f3 = 0.001f;
		ImGui::InputFloat("input z", &f3, 0.01f, 1.0f, "%.3f");
		ImGui::SetItemTooltip("Z Component of the force applied to the particule");

		if (UserForceEnabled)
			UserForce = Vector3D(f1, f2, f3);
		else
			UserForce = Vector3D(0, 0, 0);

		ImGui::Checkbox("UserForce enabled", &UserForceEnabled);
		ImGui::SetItemTooltip("Apply the force defined above to the particule");
		ImGui::Checkbox("Pause", &Paused);
		ImGui::SetItemTooltip("Pause the simulation");

		/*
		struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
		ImGuiKey start_key = (ImGuiKey)0;
		ImGui::Text("Keys down:");
		for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
		{
			if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine();
			ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key);

			if (key == ImGuiKey_W)
			{
				std::cout << "w" << std::endl;
				//func();
			}
		}
		*/
		
		ImGui::End();
		
		
		//render Imgui
		RenderFrame();


		
		Manager::ClearBGColor();

		//Draw Objects

		ParticuleObject.Draw(camera);

		ForceObj.Draw(camera);

		//Obj.Draw(camera);
		GroundObj.Draw(camera);
		//BGObj.Draw(camera);

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

	GroundObj.Delete();
	BGObj.Delete();
	ParticuleObject.Delete();

	catTex.Delete();
	brickTex.Delete();

	shaderProgramTextureBG.Delete();
	shaderProgramTextureGround.Delete();


	Manager::DeleteWindow(window);

	return 0;
}