#ifndef THREEDOBJECT_CLASS_H
#define THREEDOBJECT_CLASS_H

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include "Camera.h"
#include "Texture.h"


//Class to define a 3Dobject 
class ThreeDObject
{
public:
	struct Objreturn
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;
	};

	ThreeDObject(Shader _shaderProgram, std::vector<GLuint> _indices, std::vector<GLfloat> _values);
	~ThreeDObject();

	//Move and rotate the camera
	void SetMvt(float x, float y, float z);
	void SetRot(float Xangle, float Yangle, float Zangle); //Xangle : rotation around X
	
	//update the value of the 3D object
	void Update();
	

	//function to get and set Indicies vector and Vertex vector
	std::vector<GLuint> GetIndices();
	std::vector<GLfloat> GetValues();

	int GetIndicesLength();
	int GetValuesLength();
	int GetValuesNumber();

	void RemoveIndice(int index);
	void RemoveValue(int index);

	GLuint GetIndice(int index);
	
	//return a vertice with all the parameters
	Objreturn GetValue(int index);

	void SetIndices(std::vector<GLuint> _indices);
	void SetValues(std::vector<GLfloat> _values);

	void AddIndice(GLuint _indice);

	//add a vertice with all the parameters
	void AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void SetIndice(int index, GLuint _indice);
	void SetValue(int index, GLfloat _value);



	//draw the object
	void Draw(Camera camera);

	void Delete();

protected:
	Shader shaderProgram = Shader("OpenGL/Shaders/default.vert", "OpenGL/Shaders/default.frag");
	VAO _VAO;
	VBO _VBO;
	EBO _EBO;
	std::vector<GLuint> indices;
	std::vector<GLfloat> vertices;
};

// a 3D object with a Texture

class ThreeDObjectTexture : public ThreeDObject
{
public:
	struct Textreturn
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat textX;
		GLfloat textY;
	};

	ThreeDObjectTexture(Shader _shaderProgram, Texture _texture, std::vector<GLuint> _indices, std::vector<GLfloat> _values);

	~ThreeDObjectTexture();

	void SetMvt(float x, float y, float z);
	void SetRot(float Xangle, float Yangle, float Zangle); //Xangle : rotation around X

	void Update();

	void AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat textX, GLfloat textY);

	void Draw(Camera camera);
	
	void Delete();

	Textreturn GetValue(int index);
	void RemoveValue(int index);
	int GetValuesNumber();
private:
	Texture texture;
};

#endif