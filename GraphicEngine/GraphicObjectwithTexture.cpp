#include "GraphicObjectwithTexture.h"

GraphicObjectwithTexture::GraphicObjectwithTexture(std::string _name, Shader _shaderProgram, Texture _text) : GraphicObject(_name, _shaderProgram)
{
	name = _name;
	shaderProgram = _shaderProgram;

	_texture = _text;


	ElementToUpdate();
}

GraphicObjectwithTexture::~GraphicObjectwithTexture()
{
	Delete();
}

void GraphicObjectwithTexture::SetMvt(float x, float y, float z)
{

	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + x;
		vertices.at(i + 1) = vertices.at(i + 1) + y;
		vertices.at(i + 2) = vertices.at(i + 2) + z;

		i = i + 8;
	}
}

void GraphicObjectwithTexture::SetRot(float Xangle, float Yangle, float Zangle)
{

}

void GraphicObjectwithTexture::ElementToUpdate()
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

	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO.LinkAttrib(_VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.LinkAttrib(_VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	_VAO.Unbind();
	_VBO.Unbind();
	_EBO.Unbind();

	_texture.texUnit(shaderProgram, "tex0", 0);
}


void GraphicObjectwithTexture::Draw(Camera camera)
{
	shaderProgram.Activate(); //indicate what shader to draw

	float FOV = 45.0f;

	camera.Matrix(FOV, 0.1f, 100.0f, shaderProgram, "camMatrix"); //use the projection matrix of the camera to create perspective

	_texture.Bind();

	_VAO.Bind();//tel OpenGL what to draw

	GLuint arr[100];
	std::copy(indices.begin(), indices.end(), arr);
	glDrawElements(GL_TRIANGLES, sizeof(arr) / sizeof(int), GL_UNSIGNED_INT, 0); //draw the selected element
}


void GraphicObjectwithTexture::Delete()
{
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();

}
