#pragma once
#include "Structures.h"


class SceneObject
{
public:
	SceneObject(Model* model);
	virtual ~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

