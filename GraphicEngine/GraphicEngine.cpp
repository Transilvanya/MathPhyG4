#include "GraphicEngine.h"
#include "../OpenGL/Manager.h"
#include "../ImGui/imgui.h"
#include "../UI/ImGuiOpenGLManager.cpp"
#include "../UI/InputControler.cpp"
#include "../MainManager/MainManager.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/ThreeDObject.h"
#include "../Particules/Particules.h"
#include "../OpenGL/ParticuleObject.h"
#include <filesystem>



//function to bind to the InputControler

void cameraMoveLeft()
{

	GraphicEngine::GetInstance()->getCamera().MoveLeftCamera();
}

void cameraMoveRight()
{
	GraphicEngine::GetInstance()->getCamera().MoveRightCamera();
}

void cameraMoveFoward()
{
	GraphicEngine::GetInstance()->getCamera().MoveFowardCamera();
}

void cameraMoveBackward()
{
	GraphicEngine::GetInstance()->getCamera().MoveBackwardCamera();
}

void cameraMoveUp()
{
	GraphicEngine::GetInstance()->getCamera().MoveUpCamera();
}

void cameraMoveDown()
{
	GraphicEngine::GetInstance()->getCamera().MoveDownCamera();
}

void cameraRotation(int _xpos, int _ypos)
{
	GraphicEngine* ge = GraphicEngine::GetInstance();

	if (_xpos < ge->getWidth() / 10 || _xpos > ge->getWidth() * 9 / 10)
	{
		//	camera.RotateCamera(_xpos, _ypos );
	}
	if (_ypos < ge->getHeight() / 10 || _ypos > ge->getHeight() * 9 / 10)
	{

	}
	ge->getCamera().RotateCamera(_xpos, _ypos);
}

void cameraSettoDrift()
{
	GraphicEngine::GetInstance()->getCamera().SetCameraToDrift();
}


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


int GraphicEngine::init()
{
	//Setup OpenGL

	const char* glsl_version = "#version 130";
	GLFWwindow* window;
	
	try
	{
		
		window = Manager::InitWindow(width, height);
		
	}
	catch (InitException e)
	{
		std::cout << "InitWindow failed" << std::endl;
		return EXIT_FAILURE;
	}

	// ______________________________     ImGui Setup


	ImGuiIO& io = ImGuiSetup(window, glsl_version);
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	inputControlerBinding();

	// Generates Shader object using shaders default.vert and default.frag files
	Shader shaderProgramColor("OpenGL/Shaders/simplecolor.vert", "OpenGL/Shaders/simplecolor.frag");
	Shader shaderProgramTextureBG("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");
	Shader shaderProgramTextureGround("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");


	//create a 3D object to display
	ThreeDObject ForceObj(shaderProgramColor, Forceindice, Forcevertice);




	// Texture ______________________________________

	//Create the path to a texture
	std::string parentDir = std::filesystem::current_path().string();
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/BasicGraphicEngine/";

	// Create a texture
	Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//Create a 3Dobject with a texture
	ThreeDObject GroundObj(shaderProgramColor, groundindice, groundvertice);

	Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//Texture catTex((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	ThreeDObjectTexture BGObj(shaderProgramTextureBG, catTex, backgroundindice, backgroundvertice);

	ParticuleObject ParticuleObject2(0.0f, 0.0f, -18.0f, 0.9f, 0.0f, 0.5f, 1.0f, 1.0f);
	ParticuleObject ParticuleObject(0.0f, 0.0f, -18.0f, 0.9f, 0.0f, 0.5f, 1.0f, 1.0f);

	float x = 0.5f;
	float y = 0.5f;

	Particules particule1(Vector3D(0.0f, 0.0f, -18.0f), Vector3D(5.0f, 20.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f));
	Particules particule2(Vector3D(0.0f, 0.0f, -18.0f), Vector3D(3.0f, 40.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f));

	Vector3D gravity(0.0f, -9.8f, 0.0f);
	Vector3D NoForce(0.0f, 0.0f, 0.0f);

	particule1.setForce(gravity * particule1.getMasse());
	particule2.setForce(gravity * particule2.getMasse());

	float FrameRate = 1.0f / 60.0f;

	bool ParticuleContact = false;

	float prevx = particule1.getPostion().getX();
	float prevy = particule1.getPostion().getY();
	float prevz = particule1.getPostion().getZ();

	float prevx2 = particule2.getPostion().getX();
	float prevy2 = particule2.getPostion().getY();
	float prevz2 = particule2.getPostion().getZ();

	Vector3D UserForce(0, 0, 0);

	static bool Paused = false;
	static bool UserForceEnabled = true;





	while (!Manager::CloseMainWindow(window))
	{
		MainManager::GetInstance()->Update();
		//std::cout << ts->GetDeltaT() << std::endl;


		if (!Paused)
		{
			//ImGui::GetIO().DeltaTime;
			FrameRate = io.DeltaTime;

			particule1.intergrade(FrameRate);
			particule2.intergrade(FrameRate);


			if ((particule1.getForce() + UserForce).getX() < 0)
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
				ForceObj.SetValue(1 + 14, (particule1.getForce() + UserForce).getY());
				ForceObj.SetValue(1 + 21, 0.1f);
			}
			else
			{
				ForceObj.SetValue(1 + 14, -0.1f);
				ForceObj.SetValue(1 + 21, (particule1.getForce() + UserForce).getY());
			}
			if (particule1.getForce().getZ() < 0)
			{
				ForceObj.SetValue(2 + 28, (particule1.getForce() + UserForce).getZ());
				ForceObj.SetValue(2 + 35, 0.1f);
			}
			else
			{
				ForceObj.SetValue(2 + 28, -0.1f);
				ForceObj.SetValue(2 + 35, (particule1.getForce() + UserForce).getZ());
			}
			ForceObj.Update();

			ParticuleObject.SetMvt(particule1.getPostion().getX() - prevx, particule1.getPostion().getY() - prevy, particule1.getPostion().getZ() - prevz);
			ParticuleObject.Update();

			ParticuleObject2.SetMvt(particule2.getPostion().getX() - prevx2, particule2.getPostion().getY() - prevy2, particule2.getPostion().getZ() - prevz2);
			ParticuleObject2.Update();

			prevx = particule1.getPostion().getX();
			prevy = particule1.getPostion().getY();
			prevz = particule1.getPostion().getZ();

			prevx2 = particule2.getPostion().getX();
			prevy2 = particule2.getPostion().getY();
			prevz2 = particule2.getPostion().getZ();



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

			particule2 = Particules(Vector3D(0.0f, 0.0f, -18.0f), Vector3D(3.0f, 40.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f));
			particule2.setForce(gravity * particule2.getMasse());
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


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)  %.1f", 1000.0f / io.Framerate, io.Framerate, io.DeltaTime * 1000);
		//ImGui::Text("Delta T : %d", ts->GetDeltaT());

		ImGui::End();


		//render Imgui
		RenderFrame();



		Manager::ClearBGColor();

		//Draw Objects

		ParticuleObject.Draw(camera);
		ParticuleObject2.Draw(camera);

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



	return EXIT_SUCCESS;

}

Camera GraphicEngine::getCamera()
{
	return this->camera;
}

unsigned int GraphicEngine::getWidth()
{
	return this->width;
}

unsigned int GraphicEngine::getHeight()
{
	return this->height;
}


void GraphicEngine::inputControlerBinding()
{
	// keybind controler //

	setAfunc(cameraMoveLeft);
	setDfunc(cameraMoveRight);
	setWfunc(cameraMoveFoward);
	setSfunc(cameraMoveBackward);

	setSpacefunc(cameraMoveUp);
	setLeftCtrlfunc(cameraMoveDown);

	setMousePosfunc(cameraRotation);


	setMouseReleasefunc(cameraSettoDrift);
}




