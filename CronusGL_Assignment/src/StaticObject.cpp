#include "StaticObject.h"



StaticObject::StaticObject(Model* model, vec3 position, Rotation rotation) : SceneObject(model)
{
	_model = model;
	_position = position;
	_rotation = rotation;

	// Buffer Gen
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_Vertices.size() * sizeof(vec3), &_model->Mesh->indexed_Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_UVCoords.size() * sizeof(vec2), &_model->Mesh->indexed_UVCoords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_Normals.size() * sizeof(vec3), &_model->Mesh->indexed_Normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->Mesh->Indices.size() * sizeof(unsigned short), &_model->Mesh->Indices[0], GL_STATIC_DRAW);

	// MVP Matrix Compute
	_modelMatrix = translate(_modelMatrix, _position);
	_modelMatrix = rotate(_modelMatrix, radians(_rotation.Angle), _rotation.Axis);
	//_modelMatrix = scale(_modelMatrix, vec3(0.125f));
}


StaticObject::~StaticObject()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteBuffers(1, &_elementBuffer);
}

void StaticObject::Update()
{
}

void StaticObject::Draw()
{
	// Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _model->Texture);

	// Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Index 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	glDrawElements(GL_TRIANGLES, _model->Mesh->Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
