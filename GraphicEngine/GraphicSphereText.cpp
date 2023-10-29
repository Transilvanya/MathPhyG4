#include "GraphicSphereText.h"



GraphicSphereText::GraphicSphereText(std::string _name, Shader _shaderProgram, Texture _text, float _Radius, float _x, float _y, float _z) : GraphicObjectwithTexture(name,shaderProgram, _text)
{
	x = _x;
	y = _y;
	z = _z;
	Radius = _Radius,
	name = _name;
	shaderProgram = _shaderProgram;
	_texture = _text;

	CreateCircle();
}

GraphicSphereText::~GraphicSphereText()
{
	Delete();
}

void GraphicSphereText::CreateCircle()
{
	vertices.clear();
	indices.clear();

	float phi = 1.62f * Radius;
	


	//__	0
	vertices.push_back(x+phi);
	vertices.push_back(y+Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0);
	vertices.push_back(0);
	
	//__	1
	vertices.push_back(x+phi);
	vertices.push_back(y-Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);

	//__	2
	vertices.push_back(x-phi);
	vertices.push_back(y-Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	
	//__	3
	vertices.push_back(x-phi);
	vertices.push_back(y+Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0);
	vertices.push_back(0);
	
	//__	


	//__	4
	vertices.push_back(x+Radius);
	vertices.push_back(y);
	vertices.push_back(z+phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	5
	vertices.push_back(x-Radius);
	vertices.push_back(y);
	vertices.push_back(z+phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	6
	vertices.push_back(x-Radius);
	vertices.push_back(y);
	vertices.push_back(z-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	7
	vertices.push_back(x+Radius);
	vertices.push_back(y);
	vertices.push_back(z-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	//__


	//__	8
	vertices.push_back(x);
	vertices.push_back(y+phi);
	vertices.push_back(z+Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	
	//__	9
	vertices.push_back(x);
	vertices.push_back(y+phi);
	vertices.push_back(z-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);
	
	//__	10
	vertices.push_back(x);
	vertices.push_back(y-phi);
	vertices.push_back(z-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);
	
	//__	11
	vertices.push_back(x);
	vertices.push_back(y-phi);
	vertices.push_back(z+Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	
	vertices.push_back(0);
	vertices.push_back(0);
	//__


	//__




	indices.push_back(0);	//a
	indices.push_back(1);	//b
	indices.push_back(4);	//c

	indices.push_back(0);	//a
	indices.push_back(1);	//b
	indices.push_back(7);	//b


	indices.push_back(2);//b
	indices.push_back(3);//a
	indices.push_back(5);//c

	indices.push_back(2);//b
	indices.push_back(3);//a
	indices.push_back(6);//B


	indices.push_back(8);//b
	indices.push_back(9);//c
	indices.push_back(0);//a

	indices.push_back(8);//b
	indices.push_back(9);//c
	indices.push_back(3);//a


	indices.push_back(10);
	indices.push_back(11);//a
	indices.push_back(1);	//b

	indices.push_back(10);//c
	indices.push_back(11);//a
	indices.push_back(2);//b


	indices.push_back(5);//c
	indices.push_back(4);//c
	indices.push_back(11);//a

	indices.push_back(2);//b
	indices.push_back(5);//c
	indices.push_back(11);//a

	indices.push_back(4);//c
	indices.push_back(11);//a
	indices.push_back(1);	//b


	indices.push_back(6);//c
	indices.push_back(7);//b
	indices.push_back(10);

	indices.push_back(6);//B
	indices.push_back(10);
	indices.push_back(2);

	indices.push_back(7);//b
	indices.push_back(10);
	indices.push_back(1);	//b


	indices.push_back(8);//b
	indices.push_back(4);//c
	indices.push_back(5);

	indices.push_back(8);//b
	indices.push_back(5);//c
	indices.push_back(3);//a

	indices.push_back(8);//b
	indices.push_back(4);//c
	indices.push_back(0);//a

	
	indices.push_back(9);//c
	indices.push_back(6);//b
	indices.push_back(7);//b

	indices.push_back(9);//c
	indices.push_back(6);//B
	indices.push_back(3);//a

	indices.push_back(9);//c
	indices.push_back(7);//b
	indices.push_back(0);//a

	ElementToUpdate();
}

void GraphicSphereText::SetMvt(float _x, float _y, float _z)
{

	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + _x;
		vertices.at(i + 1) = vertices.at(i + 1) + _y;
		vertices.at(i + 2) = vertices.at(i + 2) + _z;

		i = i + 8;
	}

	x += _x;
	y += _y;
	z += _z;
}
