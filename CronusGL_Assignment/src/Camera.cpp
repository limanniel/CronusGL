#include "Camera.h"
#include <iostream>


Camera::Camera()
	: _cameraSpeed(0.0f), _cameraSensitivity(0.0f), _cameraYaw(0.0f), _cameraPitch(0.0f), _lastMouseX(400.0f), _lastMouseY(400.0f),
	W(false), S(false), A(false), D(false)
{
	_cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_viewMatrix = glm::lookAt(_cameraPosition, _cameraFront, _cameraUp);
}


Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	_cameraSpeed = 0.05f * deltaTime;
	_cameraSensitivity = 0.005f * deltaTime;

	if (W) 
		_cameraPosition += _cameraSpeed * _cameraFront;
	if (S)
		_cameraPosition -= _cameraSpeed * _cameraFront;
	if (A)
		_cameraPosition -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
	if (D)
		_cameraPosition += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;

	_viewMatrix = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
}

void Camera::UpdateCameraPosition(unsigned char key)
{
	if (key == 'w' || key == 'W') {
		W = true;
	}
	else if (key == 's' || key == 'S') {
		S = true;
	}
	else if (key == 'a' || key == 'A') {
		A = true;
	}
	else if (key == 'd' || key == 'D') {
		D = true;
	}
}

void Camera::UpdateCameraPositionUp(unsigned char key)
{
	if (key == 'w' || key == 'W') {
		W = false;
	}
	else if (key == 's' || key == 'S') {
		S = false;
	}
	else if (key == 'a' || key == 'A') {
		A = false;
	}
	else if (key == 'd' || key == 'D') {
		D = false;
	}
}

void Camera::UpdateCameraDirection(int x, int y)
{
	_cameraYaw -= _cameraSensitivity * float(800 / 2 - x);
	_cameraPitch += _cameraSensitivity * float(800 / 2 - y);

	// Pitch and Yaw constraints 
	if (_cameraYaw > 360.0f || _cameraYaw < -360.0f) {
		_cameraYaw = 0.0f;
	}
	if (_cameraPitch > 89.0f) {
		_cameraPitch = 89.0f;
	}
	else if (_cameraPitch < -89.0f) {
		_cameraPitch = -89.0f;
	}

	_cameraFront.x = cos(glm::radians(_cameraPitch)) * cos(glm::radians(_cameraYaw));
	_cameraFront.y = sin(glm::radians(_cameraPitch));
	_cameraFront.z = cos(glm::radians(_cameraPitch)) * sin(glm::radians(_cameraYaw));
}
