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
	glColor3f(0.9f, 0.5f, 0.12f);
	DrawHand();
	glPopMatrix();

	// draw left leg
	glPushMatrix();
	glTranslatef(-0.003f, 0.02f, 0.0f);
	glScalef(-1, 1, 1);
	DrawLeg();
	glPopMatrix();

	// draw hat
	glPushMatrix();
	glScalef(0.9, 0.9, 1.0);
	glTranslatef(0.2, 0.7, 0.0);
	DrawHat();
	glPopMatrix();

	// draw lefrt ear
	glPushMatrix();
	glScalef(0.3, 0.3, 1.0);
	glTranslatef(-0.75f, 0.55f, 0.0f);
	glColor3f(0.9f, 0.5f, 0.12f);
	DrawEllipse(0.3, 0.7, 0.2, 0.2);
	glColor3f(0.55f, 0.27f, 0.07f);
	DrawCircle(0.3, 0.7, 0.2, 0.2);
	glPopMatrix();

	// draw body
	glPushMatrix();
	glColor3f(0.9f, 0.5f, 0.12f);
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
	glColor3f(0.9f, 0.5f, 0.12f);
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
	glTranslatef(-0.05, 0.2, 0.0);
	DrawMouth();
	glPopMatrix();
	
	// draw right ear
	glPushMatrix();
	glScalef(0.3, 0.3, 1.0);
	glRotatef(-87, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.4f, -0.05f, 0.0f);
	glColor3f(0.9f, 0.5f, 0.12f);
	DrawEllipse(0.3, 0.7, 0.2, 0.2);
	glColor3f(0.55f, 0.27f, 0.07f);
	DrawCircle(0.3, 0.7, 0.2, 0.2, 270);
	glPopMatrix();

	// draw left eyebrow
	glPushMatrix();
	glTranslatef(-0.2f, 0.3f, 0.0f);
	glScalef(0.08, 0.08, 1.0);
	DrawEyebrow();
	glPopMatrix();

	// draw right eyebrows
	glPushMatrix();
	glRotatef(10, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.28f, 0.0f);
	glScalef(0.08, 0.08, 1.0);
	DrawEyebrow();
	glPopMatrix();
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

void CKopatych::DrawCircle(float cx, float cy, float rx, float ry, float degrees, int points, float lineWidth) {
	glLineWidth((GLfloat)lineWidth);
	const float degree = static_cast<float>(M_PI * 2.0 / points);
	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= degree * degrees; angle += degree) {
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
	glRotatef(-115, 0, 0, 1);
	DrawCircle(0.0, 0.0, 0.6, 0.5, 45, 360, 50);
}
 
void CKopatych::DrawHat()
{
	glColor3f(1.0f, 0.73f, 0.3f);

	// верхн€€ часть шапочки
	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, -0.2f);
	glVertex2f(-0.36f, -0.08f);
	glVertex2f(-0.19f, -0.08f);
	glVertex2f(-0.15f, -0.085f);
	glVertex2f(-0.12f, -0.0855f);
	glVertex2f(-0.1f, -0.09f);
	glVertex2f(0.05f, -0.13f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	// обводка
	glColor3f(0.55f, 0.27f, 0.07f);
	glLineWidth(8.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.5f, -0.2f);
	glVertex2f(-0.36f, -0.08f);
	glVertex2f(-0.19f, -0.08f);
	glVertex2f(-0.15f, -0.085f);
	glVertex2f(-0.12f, -0.0855f);
	glVertex2f(-0.1f, -0.09f);
	glVertex2f(0.05f, -0.13f);
	glVertex2f(0.2f, -0.3f);
	glEnd();

	// нижн€€ часть шапочки
	glColor3f(1.0f, 0.73f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.62f, -0.28f);
	glVertex2f(-0.65f, -0.25f);
	glVertex2f(-0.68f, -0.22f);
	glVertex2f(-0.7f, -0.2f);
	glVertex2f(-0.6f, -0.18f);
	glVertex2f(-0.5f, -0.16f);
	glVertex2f(-0.45f, -0.165f);
	glVertex2f(-0.4f, -0.17f);
	glVertex2f(-0.35f, -0.175f);
	glVertex2f(-0.3f, -0.18f);
	glVertex2f(-0.25f, -0.185f);
	glVertex2f(-0.2f, -0.19f);
	glVertex2f(-0.15f, -0.195f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(-0.05f, -0.205f);
	glVertex2f(0.0f, -0.21f);
	glVertex2f(0.05f, -0.215f);
	glVertex2f(0.1f, -0.22f);
	glVertex2f(0.13f, -0.225f);
	glVertex2f(0.3f, -0.28f);
	glVertex2f(0.35f, -0.3f);
	glVertex2f(0.2f, -0.4f);
	glEnd();

	// обводка
	glColor3f(0.55f, 0.27f, 0.07f);
	glLineWidth(8.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.6f, -0.3f);
	glVertex2f(-0.62f, -0.28f);
	glVertex2f(-0.65f, -0.25f);
	glVertex2f(-0.68f, -0.22f);
	glVertex2f(-0.7f, -0.2f);
	glVertex2f(-0.6f, -0.18f);
	glVertex2f(-0.5f, -0.16f);
	glVertex2f(-0.45f, -0.165f);
	glVertex2f(-0.4f, -0.17f);
	glVertex2f(-0.35f, -0.175f);
	glVertex2f(-0.3f, -0.18f);
	glVertex2f(-0.25f, -0.185f);
	glVertex2f(-0.2f, -0.19f);
	glVertex2f(-0.15f, -0.195f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(-0.05f, -0.205f);
	glVertex2f(0.0f, -0.21f);
	glVertex2f(0.05f, -0.215f);
	glVertex2f(0.1f, -0.22f);
	glVertex2f(0.13f, -0.225f);
	glVertex2f(0.3f, -0.28f);
	glVertex2f(0.35f, -0.3f);
	glVertex2f(0.2f, -0.4f);
	glVertex2f(-0.6f, -0.3f);
	glEnd();
}

void CKopatych::DrawEyebrow()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawEllipse(0.0f, 0.0f, 0.7f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(1.0f, 0.5f);
	glVertex2f(1.0f, -0.5f);
	glEnd();
	DrawEllipse(1.0f, 0.0f, 0.7f, 0.5f);
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

