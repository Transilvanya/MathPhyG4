#include "Manager.h"


GLFWwindow* Manager::InitWindow(const unsigned int width, const unsigned int height)
{
	//initialise OpenGL


	// Initialize GLFW
	glfwInit();


	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "BasicGraphicEngine"
	GLFWwindow* window = glfwCreateWindow(width, height, "BasicGraphicEngine", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		glfwTerminate();

		throw InitException();
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

	// Enables the Depth Buffer. tell opengl to use depth
	glEnable(GL_DEPTH_TEST);

	return window;

}

void Manager::DeleteWindow(GLFWwindow* window)
{
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

bool Manager::CloseMainWindow(GLFWwindow* window)
{
	return glfwWindowShouldClose(window);
}

void Manager::ClearBGColor()
{
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Manager::CleanElements(GLFWwindow* window)
{
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
	// Take care of all GLFW events
	glfwPollEvents();
}
