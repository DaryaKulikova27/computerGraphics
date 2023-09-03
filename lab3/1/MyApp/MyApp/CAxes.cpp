#include "CAxes.h"

CAxes::CAxes()
{}

void CAxes::Draw() const
{
	glLineWidth(3);
	glColor3f(1, 0, 0);
	DrawOs(0);
	glColor3f(0, 1, 0);
	DrawOs(90);
}

void CAxes::InitDivisions(float start, float finish, int count)
{
	m_cnt = count;
	float dx = (finish - start) / (m_cnt - 1);
	for (int i = 0; i < m_cnt; i++) {
		divisions.push_back({ start, float(sin(start)) });
		start += dx;
	}
}

void CAxes::DrawOs(float alfa) 
{
	static float d = 0.05;
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glBegin(GL_LINES);
		glVertex2f(-1, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 0);
		glVertex2f(1 - d, 0 + d);
		glVertex2f(1, 0);
		glVertex2f(1 - d, 0 - d);
	glEnd();


	for (float i = -1.0f; i < 1.1f; i += 0.1f)
	{
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(i, 0.02f);
		glVertex2f(i, -0.02f);
		glEnd();
	}
	glPopMatrix();
}