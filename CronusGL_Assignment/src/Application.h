#pragma once
#include <Windows.h>
#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "GLUTCallbacks.h"
#include "ShaderLoader.h"
#include "LoadTexture2DBMP.h"
#include "MeshLoaderOBJ.h"
#include "Camera.h"

#include "StaticObject.h"


class Application
{
private:
	//GLUT
	const int RefreshRate;
	float deltaTime;
	float lastFrame;

	// ID's
	GLuint _programID;
	GLuint _matrixID;
	GLuint _textureID;

	// Buffers
	GLuint VertexArrayID;

	// Matrices
	glm::mat4 _projectionMatrix;
	glm::mat4 _MVP;

	// Camera
	Camera* camera;

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
	void PassiveMouse(int x, int y);

	void InitObject();
};
