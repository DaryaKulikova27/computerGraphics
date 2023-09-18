#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include "BaseWindow.h"
#include "CKopatych.h"


const float DEG2RAD = 3.14159 / 180.0;

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override
	{		
		Init2DScreen(width, height);
		glPushMatrix();
		CKopatych kopatych{ {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} };
		kopatych.DrawKopatych();
		glPopMatrix();
	}

	void Init2DScreen(int width, int height)
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width, height);
		glLoadIdentity();
		SetupProjectionMatrix(width, height);
		glScalef(1.0f, 1.0f, 1.0f);
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		const double aspectRatio = double(width) / double(height);
		double viewWidth = 2.0;
		double viewHeight = viewWidth;
		if (aspectRatio > 1.0)
		{
			viewWidth = viewHeight * aspectRatio;
		}
		else
		{
			viewHeight = viewWidth / aspectRatio;
		}
		// описывает матрицу перспективы, которая создает параллельную проекцию
		glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
	}
};
