#include "DynamicObject.h"



DynamicObject::DynamicObject(Model* model, vec3 position, Rotation rotation, vec3 scale)
	: SceneObject(model, position, rotation, scale)
{
	// Buffer Gen
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_Vertices.size() * sizeof(vec3), &_model->Mesh->indexed_Vertices[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_UVCoords.size() * sizeof(vec2), &_model->Mesh->indexed_UVCoords[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->indexed_Normals.size() * sizeof(vec3), &_model->Mesh->indexed_Normals[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->Mesh->Indices.size() * sizeof(unsigned short), &_model->Mesh->Indices[0], GL_DYNAMIC_DRAW);

	// Model -> World : Matrix Compute
	_modelMatrix = glm::translate(_modelMatrix, _position);
	_modelMatrix = glm::rotate(_modelMatrix, radians(_rotation.Angle), _rotation.Axis);
	_modelMatrix = glm::scale(_modelMatrix, _scale);
}


DynamicObject::~DynamicObject()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteBuffers(1, &_elementBuffer);
}

void DynamicObject::Update()
{
}

void DynamicObject::Draw()
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

	// Normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Index 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	glDrawElements(GL_TRIANGLES, _model->Mesh->Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
