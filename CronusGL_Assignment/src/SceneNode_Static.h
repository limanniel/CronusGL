#pragma once
#include "SceneNode.h"

class SceneNode_Static : public SceneNode
{
public:
	SceneNode_Static(Model* model = nullptr, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), Rotation rotation = Rotation(), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	~SceneNode_Static();

	void Update() override;
	void Render() override;
};

