
#ifndef GRAPHICPOLYGONTEXT_CLASS_H
#define GRAPHICPOLYGONTEXT_CLASS_H


#include "GraphicObjectwithTexture.h"

class GraphicPolygonText : public GraphicObjectwithTexture
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

		GLfloat textx;
		GLfloat texty;
	};
	virtual GraphicObjectType getType() { return PolygonText; }

	GraphicPolygonText(std::string _name, Shader _shaderProgram, Texture _text, std::vector<GLuint> _indices, std::vector<GLfloat> _values, float _xanchor, float _yanchor, float _zanchor);
	~GraphicPolygonText();

	virtual void ElementToUpdate();

	virtual void SetMvt(float _x, float _y, float _z);

	virtual void SetRot(float Xangle, float Yangle, float Zangle);
	virtual void AddRot(float Xangle, float Yangle, float Zangle);


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
	void AddValue(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat textx, GLfloat texty);

	void SetIndice(int index, GLuint _indice);
	void SetValue(int index, GLfloat _value);
	//---------------------------------------------------------------------------------------------------------------------

private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float rotx = 0;
	float roty = 0;
	float rotz = 0;

};


#endif

