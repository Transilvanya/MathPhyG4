#ifndef PARTICULEOBJECT_CLASS_H
#define PARTICULEOBJECT_CLASS_H

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include "Camera.h"
#include "Texture.h"


//Class to define a 3Dobject 
class ParticuleObject
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;


	ParticuleObject(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a, GLfloat _size);
	~ParticuleObject();

	//Move and rotate the camera
	void SetMvt(float _x, float _y, float _z);

	void SetColor(GLfloat _r, GLfloat _g, GLfloat _b);

	void Update();

	//draw the object
	void Draw(Camera camera);

	void Delete();

protected:
	Shader shaderProgram = Shader("OpenGL/Shaders/simplecolor.vert", "OpenGL/Shaders/simplecolor.frag");
	VAO _VAO;
	VBO _VBO;
	EBO _EBO;
	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices;
};

#endif