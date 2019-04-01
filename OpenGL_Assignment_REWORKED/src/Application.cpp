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
	glutCreateWindow("OpenGL Destroyer");

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

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	programID = ShaderLoader::LoadShaders("src/shaders/SimpleVertexShader.vert", "src/shaders/SimpleFragmentShader.frag");

	// Matrix Set-up
	MatrixID = glGetUniformLocation(programID, "MVP");
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	//ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	ViewMatrix = glm::lookAt(
		glm::vec3(4,3,3),
		glm::vec3(0,0,0),
		glm::vec3(0,1,0)
	);
	glm::vec3 ScaleVector = glm::vec3(0.05, 0.05, 0.05);
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::scale(ModelMatrix, ScaleVector);
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	InitObject();

	// Launch Game Loop
	glutMainLoop();
}

Application::~Application()
{
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/////////////////////////////

	glUseProgram(programID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	object->Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////
	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	object->Update();

	glutPostRedisplay();
}

void Application::Keyboard(unsigned char key, int x, int y)
{
	
}

void Application::InitObject()
{
	model = new Model;
	model->Mesh = MeshLoaderOBJ::Load("res/models/cat.obj");
	model->TextureID = tex.Load("res/textures/Cat_diffuse.bmp");

	object = new StaticObject(model);
}
