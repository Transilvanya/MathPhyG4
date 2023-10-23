#include "GraphicEngine.h"

void GraphicEngine::Delete()
{


	// UI cleanup
	CleanUp();
	//

	 // Get an iterator pointing to the first element in the map
	std::map<std::string, Texture*>::iterator it = _textures.begin();

	// Iterate through the map and print the elements
	while (it != _textures.end())
	{
		it->second->Delete();
		delete(it->second);
		++it;
	}

	// Get an iterator pointing to the first element in the map
	std::map<std::string, Shader*>::iterator it2 = _shaders.begin();

	// Iterate through the map and print the elements
	while (it2 != _shaders.end())
	{
		it2->second->Delete();
		delete(it2->second); 
		++it2;
	}

	// Get an iterator pointing to the first element in the map
	std::map<std::string, GraphicObject*>::iterator it3 = _graphicobjects.begin();

	// Iterate through the map and print the elements
	while (it3 != _graphicobjects.end())
	{
		it3->second->Delete();
		delete(it3->second);
		++it3;
	}
		




	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

}

void GraphicEngine::InitOpenGL()
{
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "BasicGraphicEngine"
	window = glfwCreateWindow(width, height, "BasicGraphicEngine", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		glfwTerminate();

		throw GraphicException();
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	//allow for tranparency and blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw GraphicException();
	}
	// Enables the Depth Buffer. tell opengl to use depth
	glEnable(GL_DEPTH_TEST);
}


void GraphicEngine::Display()
{

	// ____ imgui

	//Create a new frame
	NewFrame();

	//Collect inputs
	InputControler();

	//create a ImGui window

	DisplayUI();

	//render Imgui
	RenderFrame();


	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw Objects
	
	DisplayElements();

	//Render the 3D objects
	RenderFrameData();
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
	// Take care of all GLFW events
	glfwPollEvents();
}

void GraphicEngine::DisplayElements()
{
	
	// Get an iterator pointing to the first element in the map
	std::map<std::string, GraphicObject*>::iterator it = ElementToDisplay.begin();

	// Iterate through the map and print the elements
	while (it != ElementToDisplay.end())
	{
		if (it->second->IsDisplayed())
		{
			it->second->Draw(camera);
		}
		++it;
	}

}

void GraphicEngine::DisplayUI()
{
	ImGui::Begin("Debug");
	if (ImGui::CollapsingHeader("Help"))
	{
		ImGui::SeparatorText("ABOUT THIS DEMO:");
		ImGui::BulletText("Camera controls : ZQSD (qwerty), WASD (azerty),\n crtl to go down, space to go up, mouse left click to orient the camera.");
		ImGui::BulletText("The rotation of the camera will be fixed at the center\n of the screen but will keep rotation we the mouse reach the edges.");
		ImGui::BulletText("The blue shape indicape the forces applied to the particule");
	}
	if (ImGui::Button("Button"))
	{
		pauseapp = !pauseapp;
	}
	if (ImGui::Button("Reset"))
	{
		ToReset = !ToReset;
	}

	ImGui::End();

}



// ---------------------------------------------------------------- 
//function to bind to the InputControler to control the camera

void cameraMoveLeft()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveLeftCamera();
}
void cameraMoveRight()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveRightCamera();
}
void cameraMoveFoward()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveFowardCamera();
}
void cameraMoveBackward()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveBackwardCamera();
}
void cameraMoveUp()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveUpCamera();
}
void cameraMoveDown()
{
	GraphicEngine::GetInstance()->GetCamera()->MoveDownCamera();
}
void cameraRotation(int _xpos, int _ypos)
{
	if (_xpos < GraphicEngine::GetInstance()->GetWidth() / 10 || _xpos > GraphicEngine::GetInstance()->GetWidth() * 9 / 10)
	{
		//	camera.RotateCamera(_xpos, _ypos );
	}
	if (_ypos < GraphicEngine::GetInstance()->GetHeight() / 10 || _ypos > GraphicEngine::GetInstance()->GetHeight() * 9 / 10)
	{

	}
	GraphicEngine::GetInstance()->GetCamera()->RotateCamera(_xpos, _ypos);

}
void cameraSettoDrift()
{
	GraphicEngine::GetInstance()->GetCamera()->SetCameraToDrift();
}

void LockCamera()
{
	GraphicEngine::GetInstance()->LockCameraRot();
}
void UnlockCamera()
{
	GraphicEngine::GetInstance()->UnlockCameraRot();
}



void GraphicEngine::Init()
{

	// Generates Shader object using shaders default.vert and default.frag
//	Shader shaderProgramTextureBG("GraphicEngine/OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");
//	Shader shaderProgramTextureGround("GraphicEngine/OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");


	try
	{
		InitOpenGL();
	}
	catch(GraphicException e)
	{
		//Error
	}

	InitUI();


		
	//RemoveElementFromDisplay(&GroundObj);
}


void GraphicEngine::InitUI()
{
	// ______________________________     ImGui Setup

	const char* glsl_version = "#version 130";

	ImGuiIO& io = ImGuiSetup(window, glsl_version);
	// Our states
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	setAfunc(cameraMoveLeft);
	setDfunc(cameraMoveRight);
	setWfunc(cameraMoveFoward);
	setSfunc(cameraMoveBackward);
	setSpacefunc(cameraMoveUp);
	setLeftCtrlfunc(cameraMoveDown);
	setMousePosfunc(cameraRotation);

	setMouseReleasefunc(cameraSettoDrift);



}
// ---------------------------------------------------------------- 