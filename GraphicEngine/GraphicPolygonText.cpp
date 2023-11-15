
#include "GraphicPolygonText.h"

GraphicPolygonText::GraphicPolygonText(std::string _name, Shader _shaderProgram, Texture _text, std::vector<GLuint> _indices, std::vector<GLfloat> _values, float _xanchor, float _yanchor, float _zanchor) : GraphicObjectwithTexture(_name, _shaderProgram, _text)
{

	name = _name;
	shaderProgram = _shaderProgram;
	_texture = _text;
	indices = _indices;
	vertices = _values;

	x = _xanchor;
	y = _yanchor;
	z = _zanchor;

	ElementToUpdate();
}

GraphicPolygonText::~GraphicPolygonText()
{
	Delete();
}

void GraphicPolygonText::ElementToUpdate()
{
	std::vector<GLfloat> tempvertices = vertices; 




	int i = 0;
	while (i < vertices.size())
	{
		float tempx = tempvertices.at(i);
		float tempy = tempvertices.at(i + 1);

		tempvertices.at(i) =		tempx* cos(rotz) + tempy * sin(rotz);
		tempvertices.at(i + 1) =	tempy* cos(rotz) - tempx * sin(rotz);

		i = i + 8;
	}

	i = 0;
	while (i < vertices.size())
	{
		float tempx = tempvertices.at(i);
		float tempz = tempvertices.at(i+2);

		tempvertices.at(i) =		tempx * cos(roty) +	tempz * sin(roty);
		tempvertices.at(i + 2) =	tempz * cos(roty) - tempx * sin(roty);

		i = i + 8;
	}

	i = 0;
	while (i < vertices.size())
	{
		float tempy = tempvertices.at(i + 1);
		float tempz = tempvertices.at(i + 2);

		tempvertices.at(i + 1) = tempy * cos(rotx) + tempz * sin(rotx);
		tempvertices.at(i + 2) = tempz * cos(rotx) - tempy * sin(roty);

		i = i + 8;
	}

	//move all vertices according to the inputs
	i = 0;
	while (i < vertices.size())
	{
		tempvertices.at(i) = tempvertices.at(i) + x;
		tempvertices.at(i + 1) = tempvertices.at(i + 1) + y;
		tempvertices.at(i + 2) = tempvertices.at(i + 2) + z;

		i = i + 8;
	}



	_VAO.Bind();



	// Generates Vertex Buffer Object and links it to vertices
	//store the data of the vertices
	GLfloat arr[1000];
	std::copy(tempvertices.begin(), tempvertices.end(), arr);

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


std::vector<GLuint> GraphicPolygonText::GetIndices()
{
	return indices;
}

std::vector<GLfloat> GraphicPolygonText::GetValues()
{
	return vertices;
}

int GraphicPolygonText::GetIndicesLength()
{
	return indices.size();
}

int GraphicPolygonText::GetValuesLength()
{
	return vertices.size();
}

int GraphicPolygonText::GetValuesNumber()
{
	return vertices.size() / 8;
}

void GraphicPolygonText::RemoveIndice(int index)
{
	if (index < indices.size())
		indices.erase(indices.begin() + index);
}

void GraphicPolygonText::RemoveValue(int index)
{
	if (index < vertices.size() - 8)
	{
		vertices.erase(vertices.begin() + index);
		vertices.erase(vertices.begin() + index + 1);
		vertices.erase(vertices.begin() + index + 2);
		vertices.erase(vertices.begin() + index + 3);
		vertices.erase(vertices.begin() + index + 4);
		vertices.erase(vertices.begin() + index + 5);
		vertices.erase(vertices.begin() + index + 6);
		vertices.erase(vertices.begin() + index + 7);
	}

}

GLuint GraphicPolygonText::GetIndice(int index)
{
	if (index >= indices.size())
		return NULL;

	return indices.at(index);
}

GraphicPolygonText::Objreturn GraphicPolygonText::GetValue(int index)
{
	Objreturn obj;
	if (index < vertices.size() - 8)
	{
		obj.x = vertices.at(index);
		obj.y = vertices.at(index + 1);
		obj.z = vertices.at(index + 2);

		obj.r = vertices.at(index + 3);
		obj.g = vertices.at(index + 4);
		obj.b = vertices.at(index + 5);
		
		obj.textx = vertices.at(index + 6);
		obj.texty = vertices.at(index + 7);
	}


	return obj;
}

void GraphicPolygonText::SetIndices(std::vector<GLuint> _indices)
{
	indices = _indices;
}

void GraphicPolygonText::SetValues(std::vector<GLfloat> _values)
{
	vertices = _values;
}

void GraphicPolygonText::AddIndice(GLuint _indice)
{
	indices.push_back(_indice);
}

void GraphicPolygonText::AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat textx, GLfloat texty)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(textx);
	vertices.push_back(texty);
}

void GraphicPolygonText::SetIndice(int index, GLuint _indice)
{
	if (index < indices.size())
		indices.at(index) = _indice;
}

void GraphicPolygonText::SetValue(int index, GLfloat _value)
{
	if (index < indices.size())
		vertices.at(index) = _value;
}
