#ifndef __BUTTON_H
#define __BUTTON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

struct Rect {
	float x1, y1,
		  x2, y2,
		  x3, y3,
		  x4, y4,
		  r, g, b;
};

/**
 *	Class for creating and interacting with buttons.
 */
class Button {
private:
	Rect rect;

	GLuint vao, vbo, ebo, shader;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
public:
	Button(Rect rect);
	~Button();

	void createRect();
	void draw();
	void detectClick(double x, double y);
};

#endif // !__BUTTON_h
