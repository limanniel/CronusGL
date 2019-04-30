#pragma once
#include "SceneObject.h"
class DynamicObject : public SceneObject
{
public:
	DynamicObject(Model* model, vec3 position = vec3(0.0f), Rotation rotation = Rotation(), vec3 scale = vec3(1.0f));
	~DynamicObject();

	void Update() override;
	void Draw() override;
};

