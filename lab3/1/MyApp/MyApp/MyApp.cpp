#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	//HWND hConsole = GetConsoleWindow();
	//ShowWindow(hConsole, SW_HIDE);
	GLFWInitializer initGLFW;
	Window window{ 800, 800, "Hello, triangle" };
	window.Run();
}