#include "Application.h"

Application::Application(int argc, char* argv[])
	: RefreshRate(16), deltaTime(0.0f), lastFrame(0.0f), model(nullptr), object(nullptr)
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
	_projectionMatrix = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	_MVP = glm::mat4(1.0f);

	// Handlers to Shaders
	_matrixID = glGetUniformLocation(_programID, "MVP");
	_textureID = glGetUniformLocation(_programID, "myTextureSampler"); 

	InitObject();

	// Launch Game Loop
	glutMainLoop();
}

Application::~Application()
{
	delete model;
	model = nullptr;
	delete camera;
	camera = nullptr;
	delete object;
	object = nullptr;

	glDeleteProgram(_programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////////////////////////

	glUseProgram(_programID);
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, value_ptr(_MVP)); // Transfer MVP data onto shader
	glUniform1i(_textureID, 0);

	object->Draw();

	// Rebind Buffer to nothing
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////
	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	// Get Delta Time
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	// Update Objects state and create MVP Matrix
	camera->Update(deltaTime);
	object->Update();
	_MVP = _projectionMatrix * camera->GetViewMatrix() * object->GetModelMatrix();

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
	model->Mesh = MeshLoaderOBJ::Load("res/models/Cat.obj");
	model->Texture = tex.Load("res/textures/Cat_diffuse.bmp");

	object = new StaticObject(model, vec3(0.0f, 0.0f, -2.0f));
}
