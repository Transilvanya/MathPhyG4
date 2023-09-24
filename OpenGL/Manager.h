#ifndef MANAGER_CLASS_H
#define MANAGER_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"
#include "VAO.h"
#include <vector>
#include "EBO.h"

class InitException
{
public:
	InitException() {}
	InitException(const InitException&){}
};

class Manager
{
public:
	static GLFWwindow* InitWindow(const unsigned int width, 	const unsigned int height);

	static void DeleteWindow(GLFWwindow* window);

	static bool CloseMainWindow(GLFWwindow* window);

	static void ClearBGColor();
	
	static void CleanElements(GLFWwindow* window);

private:


};

#endif