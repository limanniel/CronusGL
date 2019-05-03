#pragma once
#include "LinkedList.h"

class Application;

namespace GLUTCallbacks
{
	void Init(Application* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void PassiveMouse(int x, int y);
}