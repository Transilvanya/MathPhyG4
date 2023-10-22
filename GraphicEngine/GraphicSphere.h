
#ifndef GRAPHICSPHERE_CLASS_H
#define GRAPHICSPHERE_CLASS_H

#include "GraphicObject.h"

class GraphicSphere : public GraphicObject
{
public:

	virtual GraphicObjectType getType() { return Sphere; }

	GraphicSphere(std::string _name, Shader _shaderProgram, float _Radius, float _x, float _y, float _z, float _r, float _g, float _b, float _a);
	~GraphicSphere();

	void CreateCircle();

	virtual void SetMvt(float _x, float _y, float _z);

	//Value setter ------------------------------------------------------------------------------------------------------


	float GetRadius() {  return Radius; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetR() { return r; }
	float GetG() { return g; }
	float GetB() { return b; }
	float GetA() { return a; }

	void SetRadius(float r) { Radius = r; CreateCircle(); }
	void SetCenter(float _x, float _y, float _z) { x = _x; y = _y; z = _z; CreateCircle(); }
	void SetColor(float _r, float _g, float _b, float _a) { r = _r; g = _g; b = _b; a = _a; CreateCircle(); }
	
	//---------------------------------------------------------------------------------------------------------------------

private:

	float Radius = 1.0f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;
};

#endif

