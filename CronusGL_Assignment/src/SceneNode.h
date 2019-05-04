#pragma once
#include <list>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include "SceneObject.h"
#include "Structures.h"

class SceneNode
{
protected:
	// Node Properties
	SceneNode* _Parent;
	std::list<SceneNode*> _Child;
	std::list<SceneNode*> _Sibling;

	// Object Properties
	Model* _Model;
	glm::mat4 _WorldTransformMatrix;
	glm::mat4 _LocalTransformMatrix;
	Rotation _Rotation;
	glm::vec3 _Scale;
	glm::vec3 _Position;

	// Buffers
	GLuint _VertexBuffer{ 0 };
	GLuint _UVBuffer{ 0 };
	GLuint _NormalBuffer{ 0 };
	GLuint _ElementBuffer{ 0 };

public:
	SceneNode(Model* model = nullptr);
	virtual ~SceneNode();

	virtual void Update();
	virtual void Render();

	void Release();
	void Destroy();
	void AddChild(SceneNode* node);
	void AddSibling(SceneNode* node);

	glm::mat4 ComputeLocalTransformMatrix();
	inline const glm::mat4 GetLocalTransform() const { return _LocalTransformMatrix; }
	inline const glm::mat4 GetWorldTransform() const { return _WorldTransformMatrix; }
	inline void SetLocalTransform(const glm::mat4 matrix) { _LocalTransformMatrix = matrix; }
};

