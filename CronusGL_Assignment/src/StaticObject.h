#pragma once
#include "SceneObject.h"

class StaticObject : public SceneObject
{
private:
	

public:
	StaticObject(Model* model, vec3 position = vec3(0.0f), Rotation rotation = Rotation(), vec3 scale = vec3(1.0f));
	~StaticObject();

	void Update() override;
	void Draw() override;
};

