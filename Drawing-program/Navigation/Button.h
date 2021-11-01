#ifndef __BUTTON_H
#define __BUTTON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

/**
 *	Class for creating and interacting with buttons.
 */
class Button {
private:
	float x1, y1, 
		  x2, y2, 
		  x3, y3, 
		  x4, y4,
		  r, g, b;

	GLuint vao, vbo, ebo, shader;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
public:
	Button(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b);
	~Button();

	void createRect();
	void draw();
	void detectClick(double x, double y);
};

#endif // !__BUTTON_h
