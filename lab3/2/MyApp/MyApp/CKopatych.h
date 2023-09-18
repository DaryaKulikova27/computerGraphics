#pragma once
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct PointGL {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct ColorRGB {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

class CKopatych
{
public:
	CKopatych(PointGL translate, PointGL scale);
	void DrawKopatych() const;

private:
	PointGL m_translate;
	PointGL m_scale;

	static void DrawEllipse(float xCenter, float yCenter, float rx, float ry, float countPi = 2.0f, int points = 360);
	static void DrawCircle(float cx, float cy, float rx, float ry, int num_segments = 360, float lineWidth = 8.0);
	static void DrawHand();
	static void DrawLeg();
	static void DrawBeak();
	static void DrawEyes();
	static void DrawHat();
	static void DrawGlasses();
	static void DrawNose();
	static void DrawMouth();
	static void DrawEllipse2(float xCenter, float yCenter, float rx, float ry, float countPi = 2.0f, int points = 360);
};

