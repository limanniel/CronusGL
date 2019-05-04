#include "Application.h"

Application::Application(int argc, char* argv[])
	: RefreshRate(16), deltaTime(0.0f), lastFrame(0.0f), model(nullptr)
{
	// GLUT Init
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitContextVersion(3, 3); // Set OpenGL version to 3.3
	glutInitContextProfile(GLUT_CORE_PROFILE); // Switch to CORE profile from Debug
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500, 130);
	glutCreateWindow("CronusGL");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// GLUT sub-systems init
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(RefreshRate, GLUTCallbacks::Timer, RefreshRate);
	glutPassiveMotionFunc(GLUTCallbacks::PassiveMouse);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutIgnoreKeyRepeat(1);
	std::cout << "GLUT initialised successfully!" << std::endl;

	// GLEW Init
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Couldn't initialise GLEW!" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	glViewport(0, 0, 800, 800);

	// Basic OpenGL Init
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// VAO Init
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Load Shader
	_programID = ShaderLoader::LoadShaders("src/shaders/SimpleVertexShader.vert", "src/shaders/SimpleFragmentShader.frag");

	// Camera and and Projection Set-Up
	camera = new Camera;
	_projectionMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Handlers to Shaders
	_projectionMatrixID = glGetUniformLocation(_programID, "P");
	_viewMatrixID = glGetUniformLocation(_programID, "V");
	//_modelMatrixID = glGetUniformLocation(_programID, "M");
	_lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");
	_textureID = glGetUniformLocation(_programID, "myTextureSampler"); 

	InitObject();

	// Launch Game Loop
	glutMainLoop();

	delete this; // Left MainLoop so delete app
}

Application::~Application()
{
	glDeleteTextures(1, &model->Texture);

	delete model;
	model = nullptr;
	delete camera;
	camera = nullptr;

	glDeleteProgram(_programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////////////////////////

	glUseProgram(_programID);
	glUniformMatrix4fv(_projectionMatrixID, 1, GL_FALSE, value_ptr(_projectionMatrix)); // Transfer MVP data onto shader
	glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, value_ptr(_viewMatrix));
	glUniform3f(_lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	glUniform1i(_textureID, 0);

	_cube->Render();


	// Rebind Buffer to nothing
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////
	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	// Get Delta Time
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	// Update Objects state and assemble MVP Matrix
	camera->Update(deltaTime);
	_viewMatrix = camera->GetViewMatrix();

	_cube->Update();

	
	_lightPos = glm::vec3(4, 4, 4);

	glutPostRedisplay();
}

void Application::Keyboard(unsigned char key, int x, int y)
{
	camera->UpdateCameraPosition(key);
	// Close app when ESC is pressed
	if (key == 27) {
		glutLeaveMainLoop();
	}
}

void Application::KeyboardUp(unsigned char key, int x, int y)
{
	camera->UpdateCameraPositionUp(key);
}

void Application::PassiveMouse(int x, int y)
{
	camera->UpdateCameraDirection(x, y);
	glutWarpPointer(400, 400);
}

void Application::InitObject()
{
	model = new Model;
	model->Mesh = MeshLoaderOBJ::Load("res/models/cube.obj");
	model->Texture = tex.Load("res/textures/uvtemplate.bmp");

	_cube = new SceneNode_Static(model, vec3(0.0f, 0.0f, -2.0f), Rotation(), vec3(1.0f, 1.0f, 1.0f));
	_cube2 = new SceneNode_Static(model, vec3(0.0f, 0.0f, -2.0f), Rotation(), vec3(1.0f, 1.0f, 1.0f));
	_cube->AddChild(_cube2);
}
