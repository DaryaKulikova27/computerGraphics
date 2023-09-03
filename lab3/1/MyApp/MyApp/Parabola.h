#pragma once
#include <GLFW/glfw3.h>

struct PointGL {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class Parabola
{
public:
	Parabola(PointGL translate);
	void Draw() const;
private:
	PointGL m_translate;
};

