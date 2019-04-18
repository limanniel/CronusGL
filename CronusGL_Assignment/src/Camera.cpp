#include "Camera.h"
#include <iostream>


Camera::Camera()
	: _cameraSpeed(0.0f), _cameraSensitivity(0.0f), _cameraYaw(0.0f), _cameraPitch(0.0f), _lastMouseX(400.0f), _lastMouseY(400.0f)
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
	_cameraSpeed = 0.025f * deltaTime;
	_cameraSensitivity = 0.015f * deltaTime;
	_viewMatrix = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
}

void Camera::UpdateCameraPosition(unsigned char key)
{
	if (key == 'w' || key == 'W') {
		_cameraPosition += _cameraSpeed * _cameraFront;
	}
	else if (key == 's' || key == 'S') {
		_cameraPosition -= _cameraSpeed * _cameraFront;
	}
	else if (key == 'a' || key == 'A') {
		_cameraPosition -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
	}
	else if (key == 'd' || key == 'D') {
		_cameraPosition += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
	}
}

void Camera::UpdateCameraDirection(int x, int y)
{
	_cameraYaw -= _cameraSensitivity * float(800 / 2 - x);
	_cameraPitch += _cameraSensitivity * float(800 / 2 - y);

	// Pitch Constraint to prevent flipping camera
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
