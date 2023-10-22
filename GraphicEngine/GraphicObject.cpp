#include "GraphicObject.h"
GraphicObject::GraphicObject(std::string _name, Shader _shaderProgram)
{
	name = _name;
	shaderProgram = _shaderProgram;
	ElementToUpdate();
}

GraphicObject::~GraphicObject()
{
	Delete();
}

void GraphicObject::SetMvt(float x, float y, float z)
{
	
	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + x;
		vertices.at(i + 1) = vertices.at(i + 1) + y;
		vertices.at(i + 2) = vertices.at(i + 2) + z;

		i = i + 7;
	}
}

void GraphicObject::SetRot(float Xangle, float Yangle, float Zangle)
{

}

void GraphicObject::ElementToUpdate()
{
	_VAO.Bind();



	// Generates Vertex Buffer Object and links it to vertices
	//store the data of the vertices
	GLfloat arr[1000];
	std::copy(vertices.begin(), vertices.end(), arr);

	_VBO = VBO(arr, sizeof(arr));

	GLuint arr2[1000];
	std::copy(indices.begin(), indices.end(), arr2);
	// Generates Element Buffer Object and links it to indices
	_EBO = EBO(arr2, sizeof(arr2)); //point to the various vertices


	// Links VBO attributes such as coordinates and colors to VAO
	// add coordinate	; 0 because first attrib, size of the attrib, type, 
	// size of the value for the data of each vertex (3 for coord and 3 for color + 2 for a total of 8) , and offset (0 because start a beginning of data)

	// add color		; 1 because 2nd attrib, ,,, offset of 3 because there are 3 elements before the data of color (coord);
	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0); //layout is location in shader
	_VAO.LinkAttrib(_VBO, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	_VAO.Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}


void GraphicObject::Draw(Camera camera)
{
	shaderProgram.Activate(); //indicate what shader to draw

	float FOV = 45.0f;

	camera.Matrix(FOV, 0.1f, 100.0f, shaderProgram, "camMatrix"); //use the projection matrix of the camera to create perspective

	_VAO.Bind();//tel OpenGL what to draw

	GLuint arr[100];
	std::copy(indices.begin(), indices.end(), arr);
	glDrawElements(GL_TRIANGLES, sizeof(arr) / sizeof(int), GL_UNSIGNED_INT, 0); //draw the selected element
}


void GraphicObject::Delete()
{
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();

}
