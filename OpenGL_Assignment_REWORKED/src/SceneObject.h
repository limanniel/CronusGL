#pragma once
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
#include "Structures.h"

using namespace glm;

class SceneObject
{
protected:
	// Matrices for Graphics Pipeline, MVP being final output
	mat4 _projectionMatrix;
	mat4 _viewMatrix;
	mat4 _modelMatrix;
	mat4 _MVP;

	// Object Data
	Model* _model;
	GLuint _programID;
	GLuint _matrixID;
	GLuint _vertexBuffer;
	GLuint _uvBuffer;

public:
	SceneObject(GLuint programID, Model* model);
	virtual ~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

