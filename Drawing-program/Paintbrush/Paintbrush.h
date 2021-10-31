#ifndef __PAINTBRUSH_H
#define __PAINTBRUSH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Point.h"

#include <vector>
#include <string>
#include <map>

enum Color {
	black,
	red,
	green,
	blue
};

struct rgb {
	float r, g, b;
};

/**
 *	Class for controlling points.
 */
class Paintbrush {
private:
	std::vector<Point*> points;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	GLuint vao, vbo, ebo, shader;
	int indices_lastIndex;
	bool newPos;

	float size;
	Color color;
	std::map<Color, rgb> colors;
public:
	Paintbrush();
	~Paintbrush();

	std::vector<Point*> getPoints() { return points; }
	int getPointsSize() { return points.size(); }
	void setNewPos(bool newPos) { this->newPos = newPos; }
	void setNewColor(Color color) { this->color = color; }

	void init();
	void initColors();
	void createPoint(double x, double y);
	void createFirstPos();
	void createLine();
	std::pair<float, float> findOrthogonal(Point* point1, Point* point2);
	void draw();
};

#endif // !__PAINTBRUSH_H
