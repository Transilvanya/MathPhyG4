#include "GraphicObjectwithTexture.h"


GraphicObjectwithTexture::GraphicObjectwithTexture(std::string _name, Shader _shaderProgram, Texture _text) : GraphicObject(_name, _shaderProgram)
{
	name = _name;
	shaderProgram = _shaderProgram;

	_texture = _text;
	
	
	float v[12] = { 1.0f,0.0f,0.0f, 0,
					0.0f,1.0f,0.0f, 0,
					0.0f,0.0f,1.0f, 0,};
	mtransform = Matrice34(v);


	ElementToUpdate();
}

GraphicObjectwithTexture::~GraphicObjectwithTexture()
{
	Delete();
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



	glm::mat4x4 mat = glm::mat4x4(
		1, 0, 0, 0.0f,
		0, 1, 0, 0.0f,
		0, 0, 1, 0.0f,
		0, 0, 0, 1.0f);

	
	glm::mat4x4 mat2 = glm::mat4x4(
		mtransform.getValues(0), mtransform.getValues(1), mtransform.getValues(2), 0,
		mtransform.getValues(4), mtransform.getValues(5), mtransform.getValues(6), 0,
		mtransform.getValues(8), mtransform.getValues(9), mtransform.getValues(10), 0,
		0.0f, 0.0f, 0.0f, 1.0f);
	
	/*
	glm::mat4x4 mat2 = glm::mat4x4(
		-mtransform.getValues(0), mtransform.getValues(1), -mtransform.getValues(2), 0,
		-mtransform.getValues(4), mtransform.getValues(5), -mtransform.getValues(6), 0,
		-mtransform.getValues(8), mtransform.getValues(9), -mtransform.getValues(10), 0,
		0.0f, 0.0f, 0.0f, 1.0f);
	*/
//	std::cout << mtransform.getValues(0) << " " << mtransform.getValues(1) << " " << mtransform.getValues(2) << " " << mtransform.getValues(3) << "\n";
//	std::cout << mtransform.getValues(4) << " " << mtransform.getValues(5) << " " << mtransform.getValues(6) << " " << mtransform.getValues(7) << "\n";
//	std::cout << mtransform.getValues(8) << " " << mtransform.getValues(9) << " " << mtransform.getValues(10) << " " << mtransform.getValues(11) << "\n\n";

	glm::mat4x4 mat3 = glm::translate(glm::mat4x4(1.0f), glm::vec3(mtransform.getValues(3), mtransform.getValues(7), mtransform.getValues(11)));

	mat = mat3 * mat2 * mat;

	camera.Matrix(FOV, 0.1f, 100.0f, shaderProgram, "camMatrix"); //use the projection matrix of the camera to create perspective

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "transform"), 1, GL_FALSE, glm::value_ptr(mat));

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
