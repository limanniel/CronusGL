#pragma once
#include <glm.hpp>
#include <matrix_transform.hpp>

class Camera
{
private:
	float _cameraSpeed, _cameraSensitivity;
	float _cameraPitch, _cameraYaw;
	float _lastMouseX, _lastMouseY;

	glm::vec3 _cameraPosition;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	glm::mat4 _viewMatrix;

	// Camera Bools
	bool W, S, A, D;

public:
	Camera();
	~Camera();

	void Update(float deltaTime);
	void UpdateCameraPosition(unsigned char key);
	void UpdateCameraPositionUp(unsigned char key);
	void UpdateCameraDirection(int x, int y);

	inline glm::mat4 GetViewMatrix() const { return _viewMatrix; }
};

