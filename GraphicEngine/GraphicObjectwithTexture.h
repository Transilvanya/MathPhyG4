
#ifndef GRAPHICOBJECTWITHTEXTURE_CLASS_H
#define GRAPHICOBJECTWITHTEXTURE_CLASS_H


#include "GraphicObject.h"
#include "OpenGL/Texture.h"
#include "../PhysicEngine/Matrices/Matrice34.h"
#include "../PhysicEngine/Quaternion/Quaternion.h"
#include "../PhysicEngine/vector/Vector3D.h"


class GraphicObjectwithTexture : public GraphicObject
{
public:
	virtual GraphicObjectType getType() { return TextureObj; }

	std::string getName() { return name; }

	GraphicObjectwithTexture(std::string _name, Shader _shaderProgram, Texture _text);
	~GraphicObjectwithTexture();

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

	virtual void SetMtransform(Matrice34 _mtransform) { mtransform= _mtransform; }

protected:
	Matrice34 mtransform;

	bool Displayed = true;

	std::string name;
	Shader shaderProgram = Shader("simpletext", "GraphicEngine/OpenGL/Shaders/simpletext.vert", "GraphicEngine/OpenGL/Shaders/simpletext.frag");
	Texture _texture = Texture("bricktext", "brick.png");
	VAO _VAO;
	VBO _VBO;
	EBO _EBO;
	std::vector<GLuint> indices;
	/*
	{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
	};
	*/
	std::vector<GLfloat> vertices;
	/*
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
		0.0f, 0.8f, 0.0f,		0.92f, 0.86f, 0.76f,	0.5f, 1.0f
	};
	*/
	
};

#endif

