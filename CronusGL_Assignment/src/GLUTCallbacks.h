#pragma once

class Application;

namespace GLUTCallbacks
{
	void Init(Application* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
}