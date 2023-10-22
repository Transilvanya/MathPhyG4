#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + OrientationDrift, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

	
}



void Camera::SetPosition(glm::vec3 _position) { Position = _position; }
void Camera::SetRotation(glm::vec3 _rotation) { Orientation = _rotation; }

void Camera::MoveUpCamera() { if (MovementEnabled) { Position += speed * Up; } }
void Camera::MoveDownCamera() { if (MovementEnabled) { Position += speed * -Up; } }
void Camera::MoveFowardCamera() { if (MovementEnabled) { Position += speed * Orientation; } }
void Camera::MoveBackwardCamera() { if (MovementEnabled) { Position += speed * -Orientation; } }
void Camera::MoveLeftCamera() { if (MovementEnabled) { Position += speed * -glm::normalize(glm::cross(Orientation, Up)); } }
void Camera::MoveRightCamera() { if (MovementEnabled) { Position += speed * glm::normalize(glm::cross(Orientation, Up)); } }

void Camera::RotateCamera(float _rotX, float _rotY)
{
	if (RotationEnabled)
	{
		//Rotate the camera by following the difference between the mouse and the center of the screen.
	//when the mouse reach the edge of the screen, the camera will keep rotating




	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 
		float rotY = 0;
		float rotX = 0;


		float rotYDrift = Driftsensitivity * (float)(_rotY - (height / 2)) / height;
		float rotXDrift = Driftsensitivity * (float)(_rotX - (width / 2)) / width;

		//check if the camera as reach an edge
		if (_rotX < width * MoveCameraRatio)
		{
			rotX = sensitivity * (float)(_rotX - (width / 2)) / width;
			rotXDrift = Driftsensitivity * (float)(width * MoveCameraRatio - (width / 2)) / width;
		}
		if (_rotX > width * (1 - MoveCameraRatio))
		{
			rotX = sensitivity * (float)(_rotX - (width / 2)) / width;
			rotXDrift = Driftsensitivity * (float)(width * (1 - MoveCameraRatio) - (width / 2)) / width;
		}


		if (_rotY < height * MoveCameraRatio)
		{
			rotY = sensitivity * (float)(_rotY - (height / 2)) / height;
			rotYDrift = Driftsensitivity * (float)(height * MoveCameraRatio - (height / 2)) / height;
		}
		if (_rotY > height * (1 - MoveCameraRatio))
		{
			rotY = sensitivity * (float)(_rotY - (height / 2)) / height;
			rotYDrift = Driftsensitivity * (float)(height * (1 - MoveCameraRatio) - (height / 2)) / height;
		}


		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotY), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotX), Up);



		//OrientationDrift is used to move the camera without changind Orientation

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientationDrift = glm::rotate(Orientation, glm::radians(-rotYDrift), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientationDrift, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			OrientationDrift = newOrientationDrift;
		}

		// Rotates the Orientation left and right
		OrientationDrift = glm::rotate(OrientationDrift, glm::radians(-rotXDrift), Up);
	}
}

void Camera::SetCameraToDrift()
{
	//Recenter the Camera when the user release the mouse

	Orientation = OrientationDrift;


	glm::vec3 newOrientationDrift = glm::rotate(Orientation, glm::radians(0.0f), glm::normalize(glm::cross(Orientation, Up)));

	OrientationDrift = newOrientationDrift;

	OrientationDrift = glm::rotate(OrientationDrift, glm::radians(0.0f), Up);
}


glm::vec3 Camera::GetRotation()
{
	return Orientation;
}

glm::vec3 Camera::GetRotationDrift()
{
	return OrientationDrift;
}
