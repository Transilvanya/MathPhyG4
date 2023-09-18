#include "ThreeDObject.h"
/*	// Simple timer
double crntTime = glfwGetTime();
if (crntTime - prevTime >= 1 / 60)
{
	rotation += 0.5f;
	prevTime = crntTime;
}
*/

//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate the model to see 3d
// Outputs the positions/coordinates of all vertices
//gl_Position = proj * view * model * vec4(aPos, 1.0);

ThreeDObject::ThreeDObject(Shader _shaderProgram, std::vector<GLuint> _indices, std::vector<GLfloat> _values)
{
	shaderProgram = _shaderProgram;
	indices = _indices;
	vertices = _values;
	Update();
}

ThreeDObject::~ThreeDObject()
{
	Delete();
}

void ThreeDObject::SetMvt(float x, float y, float z)
{
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + x;
		vertices.at(i+1) = vertices.at(i+1) + y;
		vertices.at(i+2) = vertices.at(i+2) + z;

		i = i + 7;
	}
}

void ThreeDObject::SetRot(float Xangle, float Yangle, float Zangle)
{

}

void ThreeDObject::Update()
{
	_VAO.Bind();


	
	// Generates Vertex Buffer Object and links it to vertices
	//store the data of the vertices
	GLfloat arr[100];
	std::copy(vertices.begin(), vertices.end(), arr);

	_VBO = VBO(arr, sizeof(arr));

	GLuint arr2[100];
	std::copy(indices.begin(), indices.end(), arr2);
	// Generates Element Buffer Object and links it to indices
	_EBO = EBO(arr2, sizeof(arr2)); //point to the various vertices


	// Links VBO attributes such as coordinates and colors to VAO
	// add coordinate	; 0 because first attrib, size of the attrib, type, 
	// size of the value for the data of each vertex (3 for coord and 3 for color + 2 for a total of 8) , and offset (0 because start a beginning of data)

	// add color		; 1 because 2nd attrib, ,,, offset of 3 because there are 3 elements before the data of color (coord);

	/*

			VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	*/

	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0); //layout is location in shader
	_VAO.LinkAttrib(_VBO, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	_VAO.Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}

std::vector<GLuint> ThreeDObject::GetIndices()
{
	return indices;
}

std::vector<GLfloat> ThreeDObject::GetValues()
{
	return vertices;
}

GLuint ThreeDObject::GetIndice(int index)
{
	return indices.at(index);
}

GLfloat ThreeDObject::GetValue(int index)
{
	return vertices.at(index);
}

void ThreeDObject::SetIndices(std::vector<GLuint> _indices)
{
	indices = _indices;
}

void ThreeDObject::SetValues(std::vector<GLfloat> _values)
{
	vertices = _values;
}

void ThreeDObject::AddIndice(GLuint _indice)
{
	indices.push_back(_indice);
}

void ThreeDObject::AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
}

void ThreeDObject::SetIndice(int index, GLuint _indice)
{
	indices.at(index) = _indice;
}

void ThreeDObject::SetValue(int index, GLfloat _value)
{
	vertices.at(index) = _value;
}

void ThreeDObject::Draw(Camera camera)
{
	shaderProgram.Activate();

	camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

	_VAO.Bind();

	GLuint arr[100];
	std::copy(indices.begin(), indices.end(), arr);
	glDrawElements(GL_TRIANGLES, sizeof(arr) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void ThreeDObject::Delete()
{
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();

	shaderProgram.Delete();
}

/* ____________________________________ */


ThreeDObjectTexture::ThreeDObjectTexture(Shader _shaderProgram, Texture _texture, std::vector<GLuint> _indices, std::vector<GLfloat> _values) 
	: ThreeDObject(_shaderProgram, _indices, _values)
{
	shaderProgram = _shaderProgram;
	indices = _indices;
	vertices = _values;
	texture = _texture;
	Update();
}

ThreeDObjectTexture::~ThreeDObjectTexture()
{
	Delete();
}

void ThreeDObjectTexture::Draw(Camera camera)
{
	shaderProgram.Activate();

	camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

	texture.Bind();

	_VAO.Bind();

	GLuint arr[100];
	std::copy(indices.begin(), indices.end(), arr);
	glDrawElements(GL_TRIANGLES, sizeof(arr) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void ThreeDObjectTexture::AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat textX, GLfloat textY)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(textX);
	vertices.push_back(textY);
}

void ThreeDObjectTexture::SetMvt(float x, float y, float z)
{
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + x;
		vertices.at(i + 1) = vertices.at(i + 1) + y;
		vertices.at(i + 2) = vertices.at(i + 2) + z;

		i = i + 8;
	}
}

void ThreeDObjectTexture::Update()
{
	_VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	//store the data of the vertices
	GLfloat arr[100];
	std::copy(vertices.begin(), vertices.end(), arr);
	_VBO = VBO(arr, sizeof(arr));

	GLuint arr2[100];
	std::copy(indices.begin(), indices.end(), arr2);
	// Generates Element Buffer Object and links it to indices
	_EBO = EBO(arr2, sizeof(arr2)); //point to the various vertices


	// Links VBO attributes such as coordinates and colors to VAO
	// add coordinate	; 0 because first attrib, size of the attrib, type, 
	// size of the value for the data of each vertex (3 for coord and 3 for color + 2 for a total of 8) , and offset (0 because start a beginning of data)

	// add color		; 1 because 2nd attrib, ,,, offset of 3 because there are 3 elements before the data of color (coord);


	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO.LinkAttrib(_VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.LinkAttrib(_VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //layout is location in shader


	// Unbind all to prevent accidentally modifying them
	_VAO.Unbind();
	_VBO.Unbind();
	_EBO.Unbind();

	texture.texUnit(shaderProgram, "tex0", 0);
}

void ThreeDObjectTexture::Delete()
{
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();
	texture.Delete();

	shaderProgram.Delete();
}
