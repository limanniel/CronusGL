#include "SceneNode_Dynamic.h"



SceneNode_Dynamic::SceneNode_Dynamic(Model* model, glm::vec3 position, Rotation rotation, glm::vec3 scale)
	: SceneNode(model, position, rotation, scale)
{
	// Dynamic Buffer Gen
	glGenBuffers(1, &_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _Model->Mesh->indexed_Vertices.size() * sizeof(glm::vec3), &_Model->Mesh->indexed_Vertices[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, _Model->Mesh->indexed_UVCoords.size() * sizeof(glm::vec2), &_Model->Mesh->indexed_UVCoords[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, _Model->Mesh->indexed_Normals.size() * sizeof(glm::vec3), &_Model->Mesh->indexed_Normals[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Model->Mesh->Indices.size() * sizeof(unsigned short), &_Model->Mesh->Indices[0], GL_DYNAMIC_DRAW);
}


SceneNode_Dynamic::~SceneNode_Dynamic()
{
	glDeleteBuffers(1, &_VertexBuffer);
	glDeleteBuffers(1, &_UVBuffer);
	glDeleteBuffers(1, &_NormalBuffer);
	glDeleteBuffers(1, &_ElementBuffer);
}

void SceneNode_Dynamic::Update()
{
	SceneNode::Update();
}

void SceneNode_Dynamic::Render()
{
	glGetIntegerv(GL_CURRENT_PROGRAM, &_ProgramID); // Get running shader program
	_ModelMatrixID = glGetUniformLocation(_ProgramID, "M"); // create a handle with vertex shader
	glUniformMatrix4fv(_ModelMatrixID, 1, GL_FALSE, value_ptr(_WorldTransformMatrix)); // push model matrix onto vertex shader

	// Texture Unit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _Model->Texture);

	// Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _UVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _NormalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Index 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ElementBuffer);

	glDrawElements(GL_TRIANGLES, _Model->Mesh->Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	SceneNode::Render();
}
