#include "Camera_Tank.h"
#include <iostream>


Camera_Tank::Camera_Tank()
{
	_cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	_cameraYaw = 90.0f;
}


Camera_Tank::~Camera_Tank()
{
}

void Camera_Tank::Update(float deltaTime)
{
	_cameraSpeed = 0.025f * deltaTime;
	_cameraSensitivity = 0.005f * deltaTime;

	// Offsets
	_cameraPosition.z -= 40.0f;
	_cameraPosition.y = 20.0f;
	_viewMatrix = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);
}

void Camera_Tank::UpdateCameraDirection(int x, int y)
{
	_cameraYaw -= _cameraSensitivity * float(800 / 2 - x);
	_cameraPitch += _cameraSensitivity * float(800 / 2 - y);

	// Pitch and Yaw constraints 
	if (_cameraYaw > 360.0f || _cameraYaw < -360.0f)
	{
		_cameraYaw = 0.0f;
	}
	if (_cameraPitch > 89.0f)
	{
		_cameraPitch = 89.0f;
	}
	else if (_cameraPitch < -89.0f)
	{
		_cameraPitch = -89.0f;
	}

	_cameraFront.x = cos(glm::radians(_cameraPitch)) * cos(glm::radians(_cameraYaw));
	_cameraFront.y = sin(glm::radians(_cameraPitch));
	_cameraFront.z = cos(glm::radians(_cameraPitch)) * sin(glm::radians(_cameraYaw));
}
