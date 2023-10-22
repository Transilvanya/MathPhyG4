#include "GraphicSphere.h"



GraphicSphere::GraphicSphere(std::string _name, Shader _shaderProgram, float _Radius, float _x, float _y, float _z, float _r, float _g, float _b, float _a) : GraphicObject(name,shaderProgram)
{
	x = _x;
	y = _y;
	z = _z;
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	Radius = _Radius,
	name = _name;
	shaderProgram = _shaderProgram;
	CreateCircle();
}

GraphicSphere::~GraphicSphere()
{
	Delete();
}

void GraphicSphere::CreateCircle()
{
	vertices.empty();
	indices.empty();

	float phi = 1.62f * Radius;
	


	//__
	vertices.push_back(x+phi);
	vertices.push_back(y+Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x+phi);
	vertices.push_back(y-Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x-phi);
	vertices.push_back(y-Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x-phi);
	vertices.push_back(y+Radius);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__


	//__
	vertices.push_back(x+Radius);
	vertices.push_back(y);
	vertices.push_back(z+phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x-Radius);
	vertices.push_back(y);
	vertices.push_back(z+phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x-Radius);
	vertices.push_back(y);
	vertices.push_back(z-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x+Radius);
	vertices.push_back(y);
	vertices.push_back(z-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__


	//__	
	vertices.push_back(x);
	vertices.push_back(y+phi);
	vertices.push_back(z+Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x);
	vertices.push_back(y+phi);
	vertices.push_back(z-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x);
	vertices.push_back(y-phi);
	vertices.push_back(z-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__
	vertices.push_back(x);
	vertices.push_back(y-phi);
	vertices.push_back(z+Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);
	vertices.push_back(a);
	//__


	//__




	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(7);


	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(6);


	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(0);

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(3);


	indices.push_back(10);
	indices.push_back(11);
	indices.push_back(1);

	indices.push_back(10);
	indices.push_back(11);
	indices.push_back(2);


	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(11);

	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(11);

	indices.push_back(4);
	indices.push_back(11);
	indices.push_back(1);


	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(10);

	indices.push_back(6);
	indices.push_back(10);
	indices.push_back(2);

	indices.push_back(7);
	indices.push_back(10);
	indices.push_back(1);


	indices.push_back(8);
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(8);
	indices.push_back(5);
	indices.push_back(3);

	indices.push_back(8);
	indices.push_back(4);
	indices.push_back(0);

	
	indices.push_back(9);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(9);
	indices.push_back(6);
	indices.push_back(3);

	indices.push_back(9);
	indices.push_back(7);
	indices.push_back(0);

	ElementToUpdate();
}

void GraphicSphere::SetMvt(float _x, float _y, float _z)
{

	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + _x;
		vertices.at(i + 1) = vertices.at(i + 1) + _y;
		vertices.at(i + 2) = vertices.at(i + 2) + _z;

		i = i + 7;
	}

	x += _x;
	y += _y;
	z += _z;
}
