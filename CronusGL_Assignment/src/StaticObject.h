#pragma once
#include "SceneObject.h"
#include "glew.h"

class StaticObject : public SceneObject
{
private:
	vec3 _position;
	Rotation _rotation;

public:
	StaticObject(Model* model, vec3 position, Rotation = Rotation());
	~StaticObject();

	void Update();
	void Draw();
};

