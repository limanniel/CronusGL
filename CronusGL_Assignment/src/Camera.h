#pragma once
#include <glm.hpp>
#include <matrix_transform.hpp>

class Camera
{
private:
	float _cameraSpeed;

	glm::vec3 _cameraPosition;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	glm::mat4 _viewMatrix;

public:
	Camera();
	~Camera();

	void Update();
	void UpdateCameraPosition(unsigned char key);

	inline glm::mat4 GetViewMatrix() const { return _viewMatrix; }
};

