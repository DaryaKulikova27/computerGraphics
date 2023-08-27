#pragma once
#include "BaseWindow.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.8f, -0.8f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.8f, -0.8f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 0.8f);
		glEnd();
	}
};
