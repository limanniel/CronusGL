#pragma once
#include "SceneObject.h"
#include "glew.h"

class StaticObject : public SceneObject
{
private:
	Model* _model;
	GLuint vertexBuffer;
	GLuint uvBuffer;

public:
	StaticObject(Model* model);
	~StaticObject();

	void Update();
	void Draw();
};

