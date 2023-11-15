#include "GraphicSphereText.h"



/*


void GraphicSphereText::Draw(Camera camera, Quaternion q, Vector3D pos)
{


	shaderProgram.Activate(); //indicate what shader to draw
	float FOV = 45.0f;




	float newVal[12] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0
	}
	;

	Matrice34 m(newVal);
	//Quaternion q = ;
	//Vector3D pos(0, 1, 0);

	float x = 0;
	float y = 1;
	float z = 1;

	q.Normalized();

	m.SetOrientationAndPosition(Quaternion(cos(temp/2), x * sin(temp / 2), y * sin(temp/2), z * sin(temp / 2)), Vector3D(0, 0, 0));
	//m.SetOrientationAndPosition(q, Vector3D(0, 0, 0));

	//std::cout << m.getValues(0) << " " << m.getValues(1) << " " << m.getValues(2) << " " << m.getValues(3) << "\n";
	//std::cout << m.getValues(4) << " " << m.getValues(5) << " " << m.getValues(6) << " " << m.getValues(7) << "\n";
	//std::cout << m.getValues(8) << " " << m.getValues(9) << " " << m.getValues(10) << " " << m.getValues(11) << "\n\n";




	glm::mat4x4 mat = glm::mat4x4(
		1, 0, 0, 0.0f,
		0, 1, 0, 0.0f,
		0, 0, 1, 0.0f,
		0, 0, 0, 1.0f);

	glm::mat4x4 mat2 = glm::mat4x4(
		m.getValues(0), m.getValues(1), m.getValues(2), 0.0f,
		m.getValues(4), m.getValues(5), m.getValues(6), 0.0f,
		m.getValues(8), m.getValues(9), m.getValues(10), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);


	float t = sqrt(cos(temp / 2) * cos(temp / 2) + x * sin(temp / 2) * x * sin(temp / 2) + y * sin(temp / 2) * y * sin(temp / 2) + z * sin(temp / 2) * z * sin(temp / 2));

	glm::vec4 v(1, 0, 0, 1);

	glm::quat qt(cos(temp / 2)/t, x * sin(temp / 2)/t, y * sin(temp / 2)/t, z * sin(temp / 2)/t);

	//glm::quat qt(cos(temp / 2), x * sin(temp / 2), y * sin(temp / 2), z * sin(temp / 2));

	mat2 = glm::mat4_cast(qt);
	v = mat2 * v;




	std::cout << v.x << " " << v.y << " " << v.z <<"\t" << sqrt(v.x*v.x + v.y*v.y + v.z*v.z) << "\t" << t << "\n";

	temp += 0.01f;

	if (temp >= 3.14)
	{
		temp = -3.14;
	}



	glm::mat4x4 mat3 = glm::translate(glm::mat4x4(1.0f), glm::vec3(0, 3, 0));



	mat = mat2 * mat;
	mat = mat3 * mat;

	camera.Matrix(FOV, 0.1f, 100.0f, shaderProgram, "camMatrix"); //use the projection matrix of the camera to create perspective

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "transform"), 1, GL_FALSE, glm::value_ptr(mat));

	_texture.Bind();

	_VAO.Bind();//tel OpenGL what to draw

	GLuint arr[100];
	std::copy(indices.begin(), indices.end(), arr);
	glDrawElements(GL_TRIANGLES, sizeof(arr) / sizeof(int), GL_UNSIGNED_INT, 0); //draw the selected element
}


*/

GraphicSphereText::GraphicSphereText(std::string _name, Shader _shaderProgram, Texture _text, float _Radius) : GraphicObjectwithTexture(name,shaderProgram, _text)
{
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
	vertices.push_back(phi);
	vertices.push_back(Radius);
	vertices.push_back(0);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0);
	vertices.push_back(0);
	
	//__	1
	vertices.push_back(phi);
	vertices.push_back(-Radius);
	vertices.push_back(0);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);

	//__	2
	vertices.push_back(-phi);
	vertices.push_back(-Radius);
	vertices.push_back(0);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	
	//__	3
	vertices.push_back(-phi);
	vertices.push_back(Radius);
	vertices.push_back(0);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0);
	vertices.push_back(0);
	
	//__	


	//__	4
	vertices.push_back(Radius);
	vertices.push_back(0);
	vertices.push_back(phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	5
	vertices.push_back(-Radius);
	vertices.push_back(0);
	vertices.push_back(phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	6
	vertices.push_back(-Radius);
	vertices.push_back(0);
	vertices.push_back(-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	//__	7
	vertices.push_back(Radius);
	vertices.push_back(0);
	vertices.push_back(-phi);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	//__


	//__	8
	vertices.push_back(0);
	vertices.push_back(phi);
	vertices.push_back(Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(1);
	vertices.push_back(0);
	
	//__	9
	vertices.push_back(0);
	vertices.push_back(phi);
	vertices.push_back(-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);
	
	//__	10
	vertices.push_back(0);
	vertices.push_back(-phi);
	vertices.push_back(-Radius);

	vertices.push_back(r);
	vertices.push_back(g);
	vertices.push_back(b);

	vertices.push_back(0.5f);
	vertices.push_back(1);
	
	//__	11
	vertices.push_back(0);
	vertices.push_back(-phi);
	vertices.push_back(Radius);

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
/*

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
*/