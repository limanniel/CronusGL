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
#include "SceneNode_Static.h"
#include "SceneNode_Dynamic.h"

class Application
{
private:
	//GLUT
	const int RefreshRate;
	float deltaTime;
	float lastFrame;

	// ID's
	GLuint _programID;
	GLuint _projectionMatrixID, _viewMatrixID;
	GLuint _textureID;
	GLuint _lightID;

	// Buffers
	GLuint VertexArrayID;

	// Light
	glm::vec3 _lightPos;

	// Matrices
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

	// Camera
	Camera* camera;

	//Object
	LoadTexture2DBMP tex;
	Model* model;

	SceneNode* _cube;
	SceneNode* _cube2;

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
