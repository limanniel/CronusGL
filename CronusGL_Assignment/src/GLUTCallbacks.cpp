#include "GLUTCallbacks.h"
#include "Application.h"

namespace GLUTCallbacks
{
	namespace
	{
		Application* app = nullptr;
	}

	void Init(Application* gl)
	{
		app = gl;
	}

	void Display()
	{
		if (app != nullptr)
			app->Display();
	}

	void Timer(int prefferedRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		app->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(prefferedRefresh - updateTime, GLUTCallbacks::Timer, prefferedRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		app->Keyboard(key, x, y);
	}
	void KeyboardUp(unsigned char key, int x, int y)
	{
		app->KeyboardUp(key, x, y);
	}
	void PassiveMouse(int x, int y)
	{
		app->PassiveMouse(x, y);
	}
	void MenuCallback(int type)
	{
		switch (type)
		{
		case 0:
			app->SetTankCamera(true);
			break;
		case 1:
			app->SetTankCamera(false);
			break;
		case 2:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
	}
}