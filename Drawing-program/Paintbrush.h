#ifndef __PAINTBRUSH_H
#define __PAINTBRUSH_H

#include <glad/glad.h>

#include "Point.h"

#include <vector>

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
public:
	Paintbrush();
	~Paintbrush();

	std::vector<Point*> getPoints() { return points; }
	int getPointsSize() { return points.size(); }

	void init();
	void createPoint(double x, double y);
	void createLine();
	void draw();
};

#endif // !__PAINTBRUSH_H
