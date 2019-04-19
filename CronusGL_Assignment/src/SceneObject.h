#pragma once
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Structures.h"

using namespace glm;

class SceneObject
{
protected:
	mat4 _modelMatrix;

	// Object Data
	Model* _model;
	GLuint  _textureID;

	// Buffers
	GLuint _vertexBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;
	GLuint _elementBuffer;

public:
	SceneObject(Model* model);
	virtual ~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	inline glm::mat4 GetModelMatrix() const { return _modelMatrix; }
};

