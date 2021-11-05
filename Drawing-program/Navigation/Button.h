#ifndef __BUTTON_H
#define __BUTTON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Colors.h"

#include <vector>

struct Rect {
	float x1, y1,
		  x2, y2,
		  x3, y3,
		  x4, y4;
};

enum ButtonType {
	colorType,
	navType
};

/**
 *	Class for creating and interacting with buttons.
 */
class Button {
private:
	Rect rect;
	Color color;
	ButtonType type;

	GLuint vao, vbo, ebo, shader;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
public:
	Button();
	Button(Rect rect, Color color, ButtonType type);
	~Button();

	void createRect();
	void draw();
	bool detectClick(double x, double y);
};

#endif // !__BUTTON_h
