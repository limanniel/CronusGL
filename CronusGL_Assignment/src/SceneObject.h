#pragma once
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "glew.h"
#include "Structures.h"

using namespace glm;

class SceneObject
{
protected:
	mat4 _modelMatrix;
	mat4 _mvpMatrix;

	// Object Data
	Model* _model{ nullptr };
	GLuint  _textureID{ 0 };
	vec3 _position;
	Rotation _rotation;
	vec3 _scale;

	// Buffers
	GLuint _vertexBuffer{ 0 };
	GLuint _uvBuffer{ 0 };
	GLuint _normalBuffer{ 0 };
	GLuint _elementBuffer{ 0 };

public:
	SceneObject(Model* model, vec3 position = vec3(0.0f), Rotation rotation = Rotation(), vec3 scale = vec3(1.0f));
	virtual ~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	inline glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	inline glm::mat4 GetMVPMatrix() const { return _mvpMatrix; }
	inline void SetMVPMatrix(glm::mat4& perspectiveMatrix, glm::mat4& viewMatrix) { _mvpMatrix = perspectiveMatrix * viewMatrix * _modelMatrix; }
};

