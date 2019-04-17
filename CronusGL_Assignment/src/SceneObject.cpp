#include "SceneObject.h"


SceneObject::SceneObject(Model* model)
	: _model(nullptr), _textureID(0), _vertexBuffer(0), _uvBuffer(0)
{
	// Assign identity matrix to each coordinate system
	_modelMatrix = mat4(1.0f);
}


SceneObject::~SceneObject()
{
}
