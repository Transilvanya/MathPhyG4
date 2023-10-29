#ifndef GRAPHICENGINE_CLASS_H
#define GRAPHICENGINE_CLASS_H


//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



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


#include <list>
#include "../GraphicEngine/GraphicObject.h"
#include<iostream>*

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <stdio.h>

#include "UI/imgui_perso.cpp"
#include "UI/InputControler.cpp"
#include "UI/ImGuiOpenGLManager.cpp"

#include"OpenGL/Texture.h"
#include"OpenGL/shaderClass.h"
#include"OpenGL/VAO.h"
#include"OpenGL/VBO.h"
#include"OpenGL/EBO.h"
#include"OpenGL/Camera.h"
#include <map>
#include "GraphicPolygon.h"
#include "GraphicSphere.h"
#include "GraphicObjectwithTexture.h"
#include "GraphicSphereText.h"


class GraphicException
{
public:
	GraphicException() {}
	GraphicException(const GraphicException&) {}
};

class GraphicEngine
{
public:
	

	static GraphicEngine* _graphicengineptr;

	static GraphicEngine* GetInstance()
	{
		if (_graphicengineptr == nullptr)
		{
			_graphicengineptr = new GraphicEngine();
		}

		return _graphicengineptr;
	}

	void Delete();

	void AddElementToDisplay(GraphicObject* object)
	{
		object->SetDisplayed(true);
		ElementToDisplay.emplace(object->getName(), object);
	}
	void RemoveElementFromDisplay(std::string name)
	{
		
		if (ElementToDisplay.count(name))
		{
			ElementToDisplay.find(name)->second->SetDisplayed(false);
			ElementToDisplay.erase(name);
		}
		else
		{
			std::cout << "coud not remove "<< name <<" from ElementToDisplay\n";
		}
	}

	void Display();


	void Init();


	bool ShouldCloseMainWindow() { return glfwWindowShouldClose(window); }
	Camera* GetCamera() { return &camera; }
	unsigned int GetWidth() { return width; }
	unsigned int GetHeight() { return height; }

	void LockCameraMvt() { camera.MovementEnabled = false; }
	void LockCameraRot() { camera.RotationEnabled = false; }
	void UnlockCameraMvt() { camera.MovementEnabled = true; }
	void UnlockCameraRot() { camera.RotationEnabled = true; }
	void SwitchPersp() { camera.PerspectiveEnabled = !camera.PerspectiveEnabled; }


	// --------------------------------------------------------------------------------
	void CreateShader(std::string name, const char* vertexshader, const char* fragmentshader)
	{
		Shader* shaderProgramColor = new Shader(name, vertexshader, fragmentshader);
		_shaders.emplace(name, shaderProgramColor);
	}
	void CreateTexture(std::string name, std::string textname)
	{
		Texture* newtext = new Texture(name, textname);
		_textures.emplace(name, newtext);
	}

	Shader* GetShader(std::string name)
	{

		if (_shaders.count(name))
			return _shaders.find(name)->second;
		else
		{
			std::cout << "coud not get Shader "<< name <<"\n";
			return nullptr;
		}
	}
	Texture* GetTexture(std::string name)
	{

		if (_textures.count(name))
			return _textures.find(name)->second;
		else
		{
			std::cout << "coud not get Texture "<< name <<"\n";
			return nullptr;
		}
	}


	void RemoveShader(std::string name)
	{
		if (_shaders.count(name))
			_shaders.erase(name);
		else
		{
			std::cout << "coud not remove Shader " << name << "\n";
		}
	}
	void RemoveTexture(std::string name)
	{
		if (_textures.count(name))
			_textures.erase(name);
		else
		{
			std::cout << "coud not remove Texture " << name << "\n";
		}
	}

	// --------------------------------------------------------------------------------
	void CreateObject(std::string name, std::string nameshader)
	{
		Shader* s = GetShader(nameshader);
		if (s != nullptr)
		{
			GraphicObject* GO = new GraphicObject(name, *s);
			_graphicobjects.emplace(name, GO);
			ElementToDisplay.emplace(name, GO);
		}
		else
		{
			std::cout << "coud not create Object " << name << " because Shader "<<nameshader << " could not be found\n";
		}
	}
	GraphicObject* GetGraphicObject(std::string name)
	{

		if (_graphicobjects.count(name))
			return _graphicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get Object " << name << "\n";
			return nullptr;
		}
	}

	// --------------------------------------------------------------------------------
	void CreateObjectwithTexture(std::string name, std::string nameshader, std::string nametexture)
	{
		Shader* s = GetShader(nameshader);
		Texture* t = GetTexture(nametexture);
		if (s != nullptr)
		{
			if (t != nullptr)
			{
				GraphicObjectwithTexture* GO = new GraphicObjectwithTexture(name, *s, *t);
				_graphicobjects.emplace(name, GO);
				ElementToDisplay.emplace(name, GO);
			}
			else
			{
				std::cout << "coud not create Object " << name << " because Texture " << nametexture << " could not be found\n";
			}
		}
		else
		{
			std::cout << "coud not create Object " << name << " because Shader " << nameshader << " could not be found\n";
		}
	}
	GraphicObjectwithTexture* GetObjectwithTexture(std::string name)
	{
		if (_graphicobjects.count(name) && _graphicobjects.find(name)->second->getType() == 2)
			return (GraphicObjectwithTexture*)_graphicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get GraphicObjectwithTexture " << name << "\n";
			return nullptr;
		}

	}
	// --------------------------------------------------------------------------------

	
	void CreateSphereText(std::string name, std::string nameshader, std::string nametexture, float _Radius, float _x, float _y, float _z)
	{
		Shader* s = GetShader(nameshader);
		Texture* t = GetTexture(nametexture);
		if (s != nullptr)
		{
			if (t != nullptr)
			{
				GraphicSphereText* GO = new GraphicSphereText(name, *s, *t, _Radius, _x, _y, _z);
				_graphicobjects.emplace(name, GO);
				ElementToDisplay.emplace(name, GO);
			}
			else
			{
				std::cout << "coud not create Object " << name << " because Texture " << nametexture << " could not be found\n";
			}
			
		}
		else
		{
			std::cout << "coud not create GraphicObjectwithTexture " << name << " because Shader " << nameshader << " could not be found\n";
		}
	}
	GraphicSphereText* GetSphereText(std::string name)
	{

		if (_graphicobjects.count(name) && _graphicobjects.find(name)->second->getType() == 1)
			return (GraphicSphereText*)_graphicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get GraphicObjectwithTexture " << name << "\n";
			return nullptr;
		}

	}
	// --------------------------------------------------------------------------------
	void CreatePolygon(std::string name, std::string nameshader, std::vector<GLuint> _indices, std::vector<GLfloat> _values)
	{
		Shader* s = GetShader(nameshader);
		if (s != nullptr)
		{
			GraphicPolygon* GO = new GraphicPolygon(name, *s,_indices, _values);
			_graphicobjects.emplace(name, GO);
			ElementToDisplay.emplace(name, GO);
		}
		else
		{
			std::cout << "coud not create Polygon " << name << " because Shader " << nameshader << " could not be found\n";
		}
	}
	GraphicPolygon* GetPolygon(std::string name)
	{
		if (_graphicobjects.count(name) && _graphicobjects.find(name)->second->getType() == 2)
			return (GraphicPolygon*)_graphicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get Polygon " << name << "\n";
			return nullptr;
		}
			
	}
	// --------------------------------------------------------------------------------
	void CreateSphere(std::string name, std::string nameshader , float _Radius, float _x, float _y, float _z, float _r, float _g, float _b, float _a)
	{
		Shader* s = GetShader(nameshader);
		if (s != nullptr)
		{
			GraphicSphere* GO = new GraphicSphere(name, *s,_Radius, _x,_y,_z,_r,_g,_b,_a);
			_graphicobjects.emplace(name, GO);
			ElementToDisplay.emplace(name, GO);
		}
		else
		{
			std::cout << "coud not create Sphere " << name << " because Shader " << nameshader << " could not be found\n";
		}
	}
	GraphicSphere* GetSphere(std::string name)
	{

		if (_graphicobjects.count(name) && _graphicobjects.find(name)->second->getType() == 1)
			return (GraphicSphere*)_graphicobjects.find(name)->second;
		else
		{
			std::cout << "coud not get Sphere " << name << "\n";
			return nullptr;
		}

	}
	// --------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------
	void RemoveGraphicObject(std::string name)
	{
		if (_graphicobjects.count(name))
		{
			GraphicObject* temp = _graphicobjects.find(name)->second;
			_graphicobjects.erase(name);
			RemoveElementFromDisplay(name);
			temp->Delete();
			delete(temp);
		}
		else
		{
			std::cout << "coud not remove Object " << name << "\n";
		}
	}

	// --------------------------------------------------------------------------------

	std::list<std::string> GetShaders()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, Shader*>::iterator it = _shaders.begin();

		// Iterate through the map and print the elements
		while (it != _shaders.end())
		{
			output.push_back(it->first);
			++it;
		}

		return output;

	}

	std::list<std::string> GetTextures()
	{
		std::list<std::string> output;

		// Get an iterator pointing to the first element in the map
		std::map<std::string, Texture*>::iterator it = _textures.begin();

		// Iterate through the map and print the elements
		while (it != _textures.end())
		{
			output.push_back(it->first);
			++it;
		}
		return output;
	}

	bool isPaused() { return pauseapp; }

	bool shouldReset() {return ToReset;}
	void setReset(bool v) { ToReset = v; }

	bool isForce() {
		return settoForce;}
	
	float GetSimulationSpeed()
	{
		return simulationspeed;
	}
private:


	bool pauseapp = true;
	bool ToReset = false;
	bool settoForce = false;
	float simulationspeed = 1.0f;

	void InitUI();
	void InitOpenGL();

	void DisplayElements();
	void DisplayUI();

	std::map<std::string,Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, GraphicObject*> _graphicobjects;
	
	std::map<std::string, GraphicObject*> ElementToDisplay;

	const unsigned int width = 1600;
	const unsigned int height = 800;

	GLFWwindow* window;

	Camera camera = Camera(width, height, glm::vec3(0.0f, 1.0f, 20.0f));
};



#endif

