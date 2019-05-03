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
#include "LinkedList.h"

#include "StaticObject.h"
#include "DynamicObject.h"


class Application
{
private:
	//GLUT
	const int RefreshRate;
	float deltaTime;
	float lastFrame;

	// ID's
	GLuint _programID;
	GLuint _matrixID, _viewMatrixID, _modelMatrixID;
	GLuint _textureID;
	GLuint _lightID;

	// Buffers
	GLuint VertexArrayID;

	// Light
	glm::vec3 _lightPos;

	// Matrices
	glm::mat4 _projectionMatrix;
	glm::mat4 _ViewMatrix;

	// Camera
	Camera* camera;

	//Object
	LoadTexture2DBMP tex;
	Model* model;
	LinkedList* _objectList;

public:
	Application(int argc, char* argv[]);
	~Application();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void PassiveMouse(int x, int y);

	void InitObject();
};
