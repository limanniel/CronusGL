#include "StaticObject.h"



StaticObject::StaticObject(Model* model) : SceneObject(model)
{
	_model = model;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->Vertices.size() * sizeof(glm::vec3), &_model->Mesh->Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _model->Mesh->UVCoords.size() * sizeof(TexCoord), &_model->Mesh->UVCoords[0], GL_STATIC_DRAW);
}


StaticObject::~StaticObject()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
}

void StaticObject::Update()
{
}

void StaticObject::Draw()
{
	// Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _model->TextureID);
	glUniform1i(_model->TextureID, 0);

	// Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, _model->Mesh->Vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
