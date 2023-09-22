#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:


	// Stores the main vectors of the camera
	glm::vec3 Position;
	//Base Rotation of the Camera
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	//Used to keep the Camera static until it reach the border of the screen
	glm::vec3 OrientationDrift = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float MoveCameraRatio = 0.1f;
	float speed = 0.1f;
	float sensitivity = 1.0f;
	float Driftsensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);



	void SetPosition(glm::vec3 _position);
	void SetRotation(glm::vec3 _rotation);

	glm::vec3 GetRotation();
	glm::vec3 GetRotationDrift();

	void MoveUpCamera();
	void MoveDownCamera();
	void MoveFowardCamera();
	void MoveBackwardCamera();
	void MoveLeftCamera();
	void MoveRightCamera();

	void RotateCamera(float _rotX, float _rotY);
	void SetCameraToDrift();
	

};
#endif