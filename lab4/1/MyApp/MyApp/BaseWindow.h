

﻿#include "pch.h"

#pragma once

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title);

	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow();

	glm::ivec2 GetFramebufferSize() const;

	void Run();

	glm::dvec2 GetCursorPos() const;

private:
	static BaseWindow* GetBaseWindow(GLFWwindow* window);

	virtual void OnResize(int width, int height) {}
	virtual void OnMouseButton(int button, int action, int mods) {}
	virtual void OnMouseMove(double x, double y) {}
	virtual void Draw(int width, int height);
	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title);

	GLFWwindow* m_window;
};