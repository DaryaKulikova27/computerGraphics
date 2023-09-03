#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include "BaseWindow.h"
#include "CAxes.h"
#include "Parabola.h"


const float DEG2RAD = 3.14159 / 180.0;

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	void Draw(int width, int height) override
	{		
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);

		glLoadIdentity();
		SetupProjectionMatrix(width, height);

		// общее масштабирование по осям x, y и z
		glScalef(0.9f, 0.9f, 0.0f);

		glPushMatrix();
		CAxes axes;
		axes.Draw();
		glPopMatrix();

		glPushMatrix();
		Parabola parabola{ {0.0f, 0.0f, 0.0f} };
		parabola.Draw();
		glPopMatrix(); 
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		// glMatrixMode указывает, какая матрица является текущей матрицей.
		glMatrixMode(GL_PROJECTION);
		// сбрасывает матрицу обратно в состояние по умолчанию
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
		//glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
	}
};
