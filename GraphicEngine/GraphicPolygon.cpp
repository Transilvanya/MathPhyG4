
#include "GraphicPolygon.h"

GraphicPolygon::GraphicPolygon(std::string _name, Shader _shaderProgram, std::vector<GLuint> _indices, std::vector<GLfloat> _values) : GraphicObject(_name,_shaderProgram)
{

	name = _name;
	shaderProgram = _shaderProgram;
	indices = _indices;
	vertices = _values;
	ElementToUpdate();
}

GraphicPolygon::~GraphicPolygon()
{
	Delete();
}

std::vector<GLuint> GraphicPolygon::GetIndices()
{
	return indices;
}

std::vector<GLfloat> GraphicPolygon::GetValues()
{
	return vertices;
}

int GraphicPolygon::GetIndicesLength()
{
	return indices.size();
}

int GraphicPolygon::GetValuesLength()
{
	return vertices.size();
}

int GraphicPolygon::GetValuesNumber()
{
	return vertices.size() / 7;
}

void GraphicPolygon::RemoveIndice(int index)
{
	if (index < indices.size())
		indices.erase(indices.begin() + index);
}

void GraphicPolygon::RemoveValue(int index)
{
	if (index < vertices.size() - 7)
	{
		vertices.erase(vertices.begin() + index);
		vertices.erase(vertices.begin() + index + 1);
		vertices.erase(vertices.begin() + index + 2);
		vertices.erase(vertices.begin() + index + 3);
		vertices.erase(vertices.begin() + index + 4);
		vertices.erase(vertices.begin() + index + 5);
		vertices.erase(vertices.begin() + index + 6);
	}

}

GLuint GraphicPolygon::GetIndice(int index)
{
	if (index >= indices.size())
		return NULL;

	return indices.at(index);
}

GraphicPolygon::Objreturn GraphicPolygon::GetValue(int index)
{
	Objreturn obj;
	if (index < vertices.size() - 7)
	{
		obj.x = vertices.at(index);
		obj.y = vertices.at(index + 1);
		obj.z = vertices.at(index + 2);

		obj.r = vertices.at(index + 3);
		obj.g = vertices.at(index + 4);
		obj.b = vertices.at(index + 5);
		obj.a = vertices.at(index + 6);
	}


	return obj;
}

void GraphicPolygon::SetIndices(std::vector<GLuint> _indices)
{
	indices = _indices;
}

void GraphicPolygon::SetValues(std::vector<GLfloat> _values)
{
	vertices = _values;
}

void GraphicPolygon::AddIndice(GLuint _indice)
{
	indices.push_back(_indice);
}

void GraphicPolygon::AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
}

void GraphicPolygon::SetIndice(int index, GLuint _indice)
{
	if (index < indices.size())
		indices.at(index) = _indice;
}

void GraphicPolygon::SetValue(int index, GLfloat _value)
{
	if (index < indices.size())
		vertices.at(index) = _value;
}
