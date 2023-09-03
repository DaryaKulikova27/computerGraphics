#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>

struct PointFloat {
	float m_x, m_y;
	PointFloat(float x, float y) {
		m_x = x;
		m_y = y;
	}
};

class CAxes
{
public:
	CAxes();
	void Draw() const;
private:
	static void DrawOs(float alfa);
	void InitDivisions(float start, float finish, int count);
	std::vector<PointFloat> divisions;
	int m_cnt;
};
