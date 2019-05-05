#pragma once
#include "Camera.h"

class Camera_Tank : public Camera
{
public:
	Camera_Tank();
	~Camera_Tank();

	void Update(float deltaTime) override;
	void UpdateCameraDirection(int x, int y) override;
};

