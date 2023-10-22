#ifndef GRAPHICENGINE_CLASS_H
#define GRAPHICENGINE_CLASS_H

#include <list>
#include "../GraphicEngine/GraphicObject.h"
#include "../OpenGL/Camera.h"
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

	void AddElementToDisplay(GraphicObject* object)
	{
		ElementToDisplay.push_back(object);
	}

	int init();

	void update();


	// getter and setter
	GLFWwindow* window;
	ImGuiIO& io;
	Camera getCamera();
	unsigned int getWidth();
	unsigned int getHeight();

private:


	const unsigned int width = 1600;
	const unsigned int height = 800;

	Camera camera = Camera(width, height, glm::vec3(0.0f, 1.0f, 20.0f));
	
	void inputControlerBinding();
	


	std::list<GraphicObject*> ElementToDisplay;
};

#endif

