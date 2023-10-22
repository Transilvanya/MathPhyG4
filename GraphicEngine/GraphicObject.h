
#ifndef GRAPHICOBJECT_CLASS_H
#define GRAPHICOBJECT_CLASS_H

//#include "../MainEngine/Entity.h"
#include "OpenGL/Camera.h"
#include <vector>
#include "OpenGL/VAO.h"
#include "OpenGL/VBO.h"
#include "OpenGL/EBO.h"

class GraphicObject
{
public:


	enum GraphicObjectType
	{
		Default = 0,
		Sphere = 1,
		Polygon = 2,
		Texture = 3
	};
	virtual GraphicObjectType getType() { return Default; }

	std::string getName() { return name; }

	GraphicObject(std::string _name, Shader _shaderProgram);
	~GraphicObject();

	//Move and rotate the object
	virtual void SetMvt(float x, float y, float z);
	virtual void SetRot(float Xangle, float Yangle, float Zangle); //Xangle : rotation around X

	//update the value of the 3D object
	virtual void ElementToUpdate();

	//draw the object
	virtual void Draw(Camera camera);

	virtual void Delete();

	virtual bool IsDisplayed() { return Displayed; }
	virtual void SetDisplayed(bool value) { Displayed = value; }

	virtual std::string GetShaderName()
	{
		return shaderProgram.getName();
	}
protected:
	bool Displayed = true;

	std::string name;
	Shader shaderProgram = Shader("simplecolor", "GraphicEngine/OpenGL/Shaders/simplecolor.vert", "GraphicEngine/OpenGL/Shaders/simplecolor.frag");
	VAO _VAO;
	VBO _VBO;
	EBO _EBO;
	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices;
};


#endif

