#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vector>
#include "glew.h"

struct Rotation
{
	float Angle;
	glm::vec3 Axis;

	// Default Values
	Rotation() {
		Angle = 0.0f;
		Axis.x = 1.0f; Axis.y = 1.0f; Axis.z = 1.0f;
	}
	// Parameterised Constructor
	Rotation(float angle, float x, float y, float z) {
		Angle = angle;
		Axis.x = x;
		Axis.y = y;
		Axis.z = z;
	}
};

struct Mesh 
{
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> UVCoords;
	std::vector<glm::vec3> Normals;

	std::vector<unsigned short> Indices;
	std::vector<glm::vec3> indexed_Vertices;
	std::vector<glm::vec2> indexed_UVCoords;
	std::vector<glm::vec3> indexed_Normals;
};

struct Model 
{
	Mesh* Mesh;
	GLuint Texture;
};