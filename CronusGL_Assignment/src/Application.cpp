#include "Application.h"

Application::Application(int argc, char* argv[])
	: RefreshRate(16)
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
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(RefreshRate, GLUTCallbacks::Timer, RefreshRate);
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

	// Load Shaders
	_programID = ShaderLoader::LoadShaders("src/shaders/SimpleVertexShader.vert", "src/shaders/SimpleFragmentShader.frag");

	// Camera and MVP set up
	_projectionMatrix = glm::mat4(1.0f);

	camera = new Camera;
	_viewMatrix = camera->GetViewMatrix();

	_projectionMatrix = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	_matrixID = glGetUniformLocation(_programID, "MVP"); // MVP Handle
	_textureID = glGetUniformLocation(_programID, "myTextureSampler"); // Texture Samples Handle

	InitObject();

	// Launch Game Loop
	glutMainLoop();
}

Application::~Application()
{
	delete model;
	model = nullptr;
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
	camera->Update();
	object->Update();
	_MVP = _projectionMatrix * camera->GetViewMatrix() * object->GetModelMatrix();

	glutPostRedisplay();
}

void Application::Keyboard(unsigned char key, int x, int y)
{
	camera->UpdateCameraPosition(key);
}

void Application::InitObject()
{
	model = new Model;
	model->Mesh = MeshLoaderOBJ::Load("res/models/cube.obj");
	model->Texture = tex.Load("res/textures/uvtemplate.bmp");

	object = new StaticObject(model, vec3(0.0f, 0.0f, -5.0f), Rotation(-55.0f, 1.0f, 0.0f, 0.0f));
}
