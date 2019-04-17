#include "Camera.h"



Camera::Camera()
	: _cameraSpeed(0.05f)
{
	_cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_viewMatrix = glm::lookAt(_cameraPosition, _cameraFront, _cameraUp);
}


Camera::~Camera()
{
}

void Camera::Update()
{
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
