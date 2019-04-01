#include "SceneObject.h"


SceneObject::SceneObject(GLuint programID, Model* model)
{
	// Assign identity matrix to each coordinate system
	_modelMatrix = mat4(1.0f);
	_viewMatrix = mat4(1.0f);
	_projectionMatrix = mat4(1.0f);
	_projectionMatrix = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Default Projection Matrix 45 FoV, 4:3 aspect.
	_MVP = mat4(1.0f);
}


SceneObject::~SceneObject()
{
}
