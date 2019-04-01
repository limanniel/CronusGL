#pragma once
#include <Windows.h>
#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include <glm.hpp>
#include <matrix_transform.hpp>

#include "GLUTCallbacks.h"
#include "ShaderLoader.h"
#include "LoadTexture2DBMP.h"
#include "MeshLoaderOBJ.h"

#include "StaticObject.h"

class Application
{
private:
	//GLUT
	const int RefreshRate;

	// Shader
	GLuint programID;
	GLuint MatrixID;
	GLuint TextureID;

	// Buffers
	GLuint VertexArrayID;

	// Matrices
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	//Object
	LoadTexture2DBMP tex;
	Model* model;
	StaticObject* object;

public:
	Application(int argc, char* argv[]);
	~Application();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

	void InitObject();
};
