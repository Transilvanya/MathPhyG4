#include "GraphicObject.h"


GraphicObject::GraphicObject(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat size)
{
	vect.setX(x);
	vect.setY(y);
	vect.setZ(z);
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;


	//std::cout << x << " " << y << " " << z << " " << r << " " << g << " " << b << " " << a << "\n";

	// Point 1

	vertices.push_back(x + size);
	vertices.push_back(y);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Point 2

	vertices.push_back(x);
	vertices.push_back(y + size);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Point 3

	vertices.push_back(x - size);
	vertices.push_back(y);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Point 4

	vertices.push_back(x);
	vertices.push_back(y - size);
	vertices.push_back(z);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Point 5

	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z + size);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Point 6

	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z - size);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(a);

	// Triangle 1

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	// Triangle 2

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(4);

	// Triangle 3

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);

	// Triangle 4

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	// Triangle 5

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(5);

	// Triangle 6

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(5);

	// Triangle 7

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(5);

	// Triangle 8

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(5);


	Update();
}

GraphicObject::GraphicObject() {

}

GraphicObject::GraphicObject(Vector3D vect, GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a, GLfloat _size)
{
	this->vect = Vector3D(vect.getX(), vect.getY(), vect.getZ());
	this->r = _r;
	this->g = _g;
	this->b = _b;
	this->a = _a;


	//std::cout << x << " " << y << " " << z << " " << r << " " << g << " " << b << " " << a << "\n";

	// Point 1

	vertices.push_back(this->vect.getX() + _size);
	vertices.push_back(this->vect.getY());
	vertices.push_back(this->vect.getZ());

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(a);

	// Point 2

	vertices.push_back(this->vect.getX());
	vertices.push_back(this->vect.getY() + _size);
	vertices.push_back(this->vect.getZ());

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(_a);

	// Point 3


	vertices.push_back(this->vect.getX() - _size);
	vertices.push_back(this->vect.getY());
	vertices.push_back(this->vect.getZ());

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(_a);

	// Point 4
	vertices.push_back(this->vect.getX());
	vertices.push_back(this->vect.getY() - _size);
	vertices.push_back(this->vect.getZ());

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(_a);

	// Point 5

	vertices.push_back(this->vect.getX());
	vertices.push_back(this->vect.getY());
	vertices.push_back(this->vect.getZ() + _size);

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(_a);

	// Point 6

	vertices.push_back(this->vect.getX());
	vertices.push_back(this->vect.getY());
	vertices.push_back(this->vect.getZ() - _size);

	vertices.push_back(_r);
	vertices.push_back(_g);
	vertices.push_back(_b);

	vertices.push_back(_a);

	// Triangle 1

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	// Triangle 2

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(4);

	// Triangle 3

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);

	// Triangle 4

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	// Triangle 5

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(5);

	// Triangle 6

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(5);

	// Triangle 7

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(5);

	// Triangle 8

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(5);


	Update();
}

GraphicObject::~GraphicObject()
{
	Delete();
}


void GraphicObject::SetMvt(float _x, float _y, float _z)
{
	this->vect.setX(vect.getX() + _x);
	this->vect.setY(vect.getY() + _y);
	this->vect.setZ(vect.getZ() + _z);
	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i) = vertices.at(i) + _x;
		vertices.at(i + 1) = vertices.at(i + 1) + _y;
		vertices.at(i + 2) = vertices.at(i + 2) + _z;

		i = i + 7;
	}
}

void GraphicObject::SetColor(GLfloat _r, GLfloat _g, GLfloat _b)
{
	r = _r;
	g = _g;
	b = _b;
	//move all vertices according to the inputs
	int i = 0;
	while (i < vertices.size())
	{
		vertices.at(i + 3) = _r;
		vertices.at(i + 4) = _g;
		vertices.at(i + 5) = _b;

		i = i + 7;
	}
}



void GraphicObject::Update()
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

	camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); //use the projection matrix of the camera to create perspective

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

	shaderProgram.Delete();
}
