#ifndef GRAPHICOBJECT_CLASS_H
#define GRAPHICOBJECT_CLASS_H

#include "../OpenGL/shaderClass.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/EBO.h"
#include "../OpenGL/Camera.h"
#include <vector>
#include "../OpenGL/Texture.h"
#include "../vector/Vector3D.h"


class GraphicObject
{
public :
	Vector3D vect;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
	GraphicObject();
	GraphicObject(Vector3D vect, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a, GLfloat _size);
	GraphicObject(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a, GLfloat _size);
	~GraphicObject();

	//Move and rotate the camera
	void SetMvt(float _x, float _y, float _z);

	void SetMvt(Vector3D vect);

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

