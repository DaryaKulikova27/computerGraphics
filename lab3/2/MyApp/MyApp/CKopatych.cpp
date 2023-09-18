#include "CKopatych.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

CKopatych::CKopatych(PointGL translate, PointGL scale)
	: m_translate(translate),
	m_scale(scale) {};

void CKopatych::DrawKopatych() const
{
	glTranslatef(m_translate.x, m_translate.y, m_translate.z);
	glScalef(m_scale.x, m_scale.y, m_scale.z);

	// draw left hand
	glPushMatrix();
	glTranslatef(-0.4, -0.02, 0.0);
	glRotatef(-15, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.55f, 0.0f);
	DrawHand();
	glPopMatrix();

	// draw left leg
	glPushMatrix();
	glTranslatef(-0.003f, 0.02f, 0.0f);
	glScalef(-1, 1, 1);
	DrawLeg();
	glPopMatrix();

	// draw body
	glPushMatrix();
	glColor3f(1.0f, 0.55f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.4, 0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.55f, 0.27f, 0.07f);
	DrawCircle(0.0f, 0.0f, 0.4, 0.4, 360);
	glPopMatrix();

	// draw right hand
	glPushMatrix();
	glRotatef(200, 0, 0, 0);
	glTranslatef(-0.4, 0.05, 0.0);
	glColor3f(1.0f, 0.55f, 0.0f);
	DrawHand();
	glPopMatrix();

	// draw right leg
	glPushMatrix();
	DrawLeg();
	glPopMatrix();

	// draw eyes
	glPushMatrix();
	glTranslatef(-0.15, 0.14, 0.0);
	glScalef(0.6, 0.6, 1.0);
	DrawEyes();
	glPopMatrix();

	// draw nose
	glPushMatrix();
	glScalef(0.2, 0.2, 1.0);
	glTranslatef(-0.4, 0.0, 0.0);
	DrawNose();
	glPopMatrix();

	// draw mouth
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);
	glTranslatef(-0.2, -0.2, 0.0);
	DrawMouth();
	glPopMatrix();



	/*
	glPushMatrix();
	glTranslatef(-0.5, 0.4, 0.0);
	glRotatef(100, 0.0, 0.0, 1.0);
	DrawHand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.3, 0.0);
	glRotatef(-60, 0.0, 0.0, 1.0);
	DrawHand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.3, 0.0);
	glRotatef(-70, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawLeg();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse2(0.0f, 0.0f, 0.5f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(200, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(0.0f, 0.0f, 0.47f, 0.47f, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.31, 0.0);
	glRotatef(-25, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse2(0.0f, 0.0f, 0.35f, 0.5f, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.32, 0.0);
	glRotatef(-25, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(0.0f, 0.0f, 0.314f, 0.23f, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.18, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.3, 0.3, 1);
	DrawBeak();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.01, 0.35, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.8, 0.8, 1);
	DrawEyes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, 0.3, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.8, 0.8, 1);
	DrawEyes();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15, 0.51, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawHat();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.13, 0.45, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);
	glScalef(0.3, 0.3, 1);
	DrawGlasses();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(-50, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.5, 1);
	DrawLeg();
	glPopMatrix(); */
}

void CKopatych::DrawEllipse2(float xCenter, float yCenter, float rx, float ry, float countPi, int points)
{
	const float step = static_cast<float>(M_PI * countPi / points);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(xCenter, yCenter);
	for (float angle = 0; angle <= M_PI * countPi; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - M_PI * countPi)) < 1e-5) ? 0 : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void CKopatych::DrawEllipse(float xCenter, float yCenter, float rx, float ry, float countPi, int points)
{
	const float degree = static_cast<float>(M_PI * countPi / points);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(xCenter, yCenter);
	for (float angle = 0; angle <= M_PI * countPi; angle += degree)
	{
		const float dx = rx * cosf(angle);
		const float dy = ry * sinf(angle);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void CKopatych::DrawCircle(float cx, float cy, float rx, float ry, int num_segments, float lineWidth) {
	glLineWidth((GLfloat)lineWidth);
	const float degree = static_cast<float>(M_PI * 2.0 / num_segments);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle <= M_PI * 2.0; angle += degree) {
		const float dx = rx * cosf(angle);
		const float dy = ry * sinf(angle);
		glVertex2f(dx + cx, dy + cy);
	}
	glEnd();
}

void CKopatych::DrawLeg()
{
	glTranslatef(0.1, -0.45, 0.0);
	glRotatef(85, 0.0f, 0.0f, 1.0f);
	glScalef(0.15, 0.15, 1);
	DrawEllipse(0.0f, 0.0f, 0.7f, 0.4f);
	glTranslatef(-0.35, -0.3, 0.0);
	glScalef(0.9, 0.9, 1);
	glRotatef(-85, 0.0f, 0.0f, 1.0f);
	DrawEllipse(0.0f, 0.0f, 0.7f, 0.5f);
}

void CKopatych::DrawBeak() {
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse2(-0.6f, 0.0f, 0.2f, 0.2f);

	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse2(0.6f, 0.0f, 0.2f, 0.2f);

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawEllipse2(0.0f, 0.4f, 0.3f, 0.2f, 1.0f);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.6f, 0.2f);
	glVertex2f(-0.6f, -0.2f);
	glVertex2f(-0.3f, -0.4f);
	glVertex2f(0.3f, -0.4f);
	glVertex2f(0.6f, -0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.05f, 0.4f);
	glVertex2f(-0.05f, 0.4f);
	glEnd();
}

void CKopatych::DrawEyes()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(10, 0.0, 0.0, 1.0);
	DrawEllipse(0.0, 0.0, 0.18, 0.2);
	glColor3f(0.55f, 0.27f, 0.07f);
	DrawCircle(0.0, 0.0, 0.18, 0.2);

	glColor3f(0.0f, 0.0f, 0.0f);
	glScalef(0.3, 0.3, 1.0);
	DrawEllipse(0.0, 0.0, 0.2, 0.2); 
	glPopMatrix();

	glTranslatef(0.28, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse(0.0, 0.0, 0.2, 0.2);
	glColor3f(0.55f, 0.27f, 0.07f);
	DrawCircle(0.0, 0.0, 0.2, 0.2);

	glColor3f(0.0f, 0.0f, 0.0f);
	glScalef(0.4, 0.4, 1.0);
	DrawEllipse(0.0, 0.0, 0.2, 0.2);
}

void CKopatych::DrawNose()
{
	glColor3f(0.32, 0.07, 0.07);
	DrawEllipse(0.0, 0.0, 0.6, 0.4);
}

void CKopatych::DrawMouth()
{
	glColor3f(0.32, 0.07, 0.07);
	glLineWidth(15.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.4, 0.0);
	glVertex2f(0.0, -0.2);
	glVertex2f(0.4, 0.0);
	glEnd();
}

void CKopatych::DrawHat()
{
	glColor3f(0.7f, 0.4f, 0.0f);
	//glColor3f(hatColor.red, hatColor.green, hatColor.blue);
	DrawEllipse2(-0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(-0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(0.7f, 0.4f, 0.0f);
	DrawEllipse2(0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(0.7f, 0.4f, 0.0f);
	DrawEllipse2(0.0f, 0.3f, 0.4f, 0.3f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.4f, 0.31f);
	glVertex2f(0.4f, 0.31f);
	glVertex2f(0.6f, -0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(-0.8f, -0.1f);
	glVertex2f(-0.5f, -0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.8f, -0.1f);
	glVertex2f(0.5f, -0.1f);
	glEnd();
	glColor3f(0.7f, 0.4f, 0.0f);
	DrawEllipse2(-0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(-0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(0.7f, 0.4f, 0.0f);
	DrawEllipse2(0.8f, 0.0f, 0.3f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawEllipse2(0.7f, 0.3f, 0.4f, 0.4f);

	glColor3f(0.7f, 0.4f, 0.0f);
	DrawEllipse(0.0f, 0.3f, 0.4f, 0.3f, 1.0f);

	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.4f, 0.31f);
	glVertex2f(0.4f, 0.31f);
	glVertex2f(0.6f, -0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(-0.8f, -0.1f);
	glVertex2f(-0.5f, -0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.8f, -0.1f);
	glVertex2f(0.5f, -0.1f);
	glEnd();
}

void CKopatych::DrawGlasses()
{
	glColor3f(0.5f, 0.2f, 0.0f);

	DrawEllipse2(-0.2f, 0.0f, 0.3f, 0.3f);

	DrawEllipse2(0.2f, 0.0f, 0.3f, 0.3f);

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(-0.2f, 0.3f);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(0.2f, 0.3f);
	glVertex2f(0.8f, 0.3f);
	glVertex2f(0.8f, -0.3f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	glColor3f(0.5f, 1.0f, 1.0f);

	DrawEllipse(-0.2f, 0.0f, 0.15f, 0.15f);

	glBegin(GL_QUADS);
	glVertex2f(-0.2f, 0.15f);
	glVertex2f(-0.6f, 0.15f);
	glVertex2f(-0.6f, -0.15f);
	glVertex2f(-0.2f, -0.15f);
	glEnd();

	DrawEllipse2(0.2f, 0.0f, 0.15f, 0.15f);

	glBegin(GL_QUADS);
	glVertex2f(0.2f, 0.15f);
	glVertex2f(0.6f, 0.15f);
	glVertex2f(0.6f, -0.15f);
	glVertex2f(0.2f, -0.15f);
	glEnd();
}

void CKopatych::DrawHand()
{
	glPushMatrix();
	glScalef(0.4, 0.4, 1.0);
	glRotatef(-40, 0.0, 0.0, 1.0);
	DrawEllipse(0.0f, 0.0f, 0.4f, 0.2f);
	glTranslatef(-0.3, 0.1, 0.0);
	glRotatef(-60, 0.0, 0.0, 1.0);
	glScalef(0.9, 0.9, 1.0);
	DrawEllipse(0.0f, 0.0f, 0.3f, 0.2f);
	glPopMatrix();
}

