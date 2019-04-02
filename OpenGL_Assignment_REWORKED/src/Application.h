#pragma once
#include <Windows.h>
#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "GLUTCallbacks.h"
#include "ShaderLoader.h"
#include "LoadTexture2DBMP.h"
#include "MeshLoaderOBJ.h"

#include "StaticObject.h"

#define AMOUNT_OF_CUBES 5

class Application
{
private:
	//GLUT
	const int RefreshRate;

	// Shader
	GLuint programID;
	GLuint MatrixID;

	// Buffers
	GLuint VertexArrayID;

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
