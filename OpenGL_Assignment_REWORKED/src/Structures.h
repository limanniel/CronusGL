#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vector>
#include "glew.h"

struct Vector3
{
	float x;
	float y;
	float z;
};

struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

struct Mesh 
{
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> UVCoords;
	std::vector<glm::vec3> Normals;
};

struct Model 
{
	Mesh* Mesh;
	GLuint TextureID;
};