#include "SceneObject.h"


SceneObject::SceneObject(Model* model, vec3 position, Rotation rotation, vec3 scale)
{
	_model = model;
	_position = position;
	_rotation = rotation;
	_scale = scale;

	// Assign identity matrices
	_modelMatrix = mat4(1.0f);
	_mvpMatrix = mat4(1.0f);
}


SceneObject::~SceneObject()
{
}
