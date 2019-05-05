#pragma once
#include <Windows.h>
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <matrix_decompose.hpp>

#include "GLUTCallbacks.h"
#include "ShaderLoader.h"
#include "LoadTexture2DBMP.h"
#include "MeshLoaderOBJ.h"
#include "Camera.h"
#include "Camera_Tank.h"

#include "LinkedList.h"
#include "SceneNode_Static.h"
#include "SceneNode_Dynamic.h"

#include "Tank.h"
#include "Scene.h"

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
	Camera* _camera;
	Camera_Tank* _tankCamera;
	bool TANK_CAMERA{ false };

	//Objects
	Scene* _scene;
	Tank* _tank;

public:
	Application(int argc, char* argv[]);
	~Application();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void PassiveMouse(int x, int y);

	void InitObject();

	inline const bool GetTankCamera() const { return TANK_CAMERA; }
	inline void SetTankCamera(bool state) { TANK_CAMERA = state; }
};
