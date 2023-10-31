#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
	//HWND hConsole = GetConsoleWindow();
	//ShowWindow(hConsole, SW_HIDE);
	GLFWInitializer initGLFW;
	Window window{ 1000, 800, "Figure" };
	window.Run();
}