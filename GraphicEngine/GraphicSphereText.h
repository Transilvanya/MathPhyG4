
#ifndef GRAPHICSPHERETEXT_CLASS_H
#define GRAPHICSPHERETEXT_CLASS_H

#include "GraphicObjectwithTexture.h"

class GraphicSphereText : public GraphicObjectwithTexture
{
public:

	

	virtual GraphicObjectType getType() { return SphereText; }

	GraphicSphereText(std::string _name, Shader _shaderProgram, Texture _text, float _Radius);
	~GraphicSphereText();

	void CreateCircle();

	//Value setter ------------------------------------------------------------------------------------------------------


	float GetRadius() {  return Radius; }
	//float GetX() { return x; }
	//float GetY() { return y; }
	//float GetZ() { return z; }

	void SetRadius(float r) { Radius = r; CreateCircle(); }
	//void SetCenter(float _x, float _y, float _z) { x = _x; y = _y; z = _z; CreateCircle(); }
	//---------------------------------------------------------------------------------------------------------------------

private:

	float Radius = 1.0f;

	//float x = 0.0f;
	//float y = 0.0f;
	//float z = 0.0f;

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
};

#endif

