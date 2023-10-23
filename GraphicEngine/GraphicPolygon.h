
#ifndef GRAPHICPOLYGON_CLASS_H
#define GRAPHICPOLYGON_CLASS_H


#include "GraphicObject.h"

class GraphicPolygon : public GraphicObject
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
	virtual GraphicObjectType getType() { return Polygon; }

	GraphicPolygon(std::string _name, Shader _shaderProgram, std::vector<GLuint> _indices, std::vector<GLfloat> _values);
	~GraphicPolygon();


	//Value setter ------------------------------------------------------------------------------------------------------
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
	//---------------------------------------------------------------------------------------------------------------------

private:

};


#endif

