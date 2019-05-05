#pragma once
#include <list>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Structures.h"

class SceneNode
{
protected:
	// Node Properties
	SceneNode* _Parent;
	std::list<SceneNode*> _Child;
	std::list<SceneNode*> _Sibling;

	GLint _ProgramID{ 0 };
	GLuint _ModelMatrixID{ 0 };

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
	SceneNode(Model* model = nullptr, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), Rotation rotation = Rotation(), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~SceneNode();

	virtual void Update();
	virtual void Render();

	void Release();
	void Destroy();
	void AddChild(SceneNode* node);
	void AddSibling(SceneNode* node);

	void ComputeLocalTransformMatrix();
	// Matrices Getters/Setters
	inline const glm::mat4 GetLocalTransform() const { return _LocalTransformMatrix; }
	inline const glm::mat4 GetWorldTransform() const { return _WorldTransformMatrix; }
	inline void SetLocalTransform(const glm::mat4 matrix) { _LocalTransformMatrix = matrix; }

	// Object Properties Getters/Setters
	inline const glm::vec3 GetPosition() const { return _Position; }
	inline void SetPosition(glm::vec3 position) { _Position = position; }
	inline const Rotation GetRotation() const { return _Rotation; }
	inline void SetRotation(Rotation rotation) { _Rotation = rotation; }
	inline const glm::vec3 GetScale() const { return _Scale; }
	inline void SetScale(glm::vec3 scale) { _Scale = scale; }
};
