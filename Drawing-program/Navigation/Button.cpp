#include "Button.h"

#include "../functions.h"
#include "../shaders/buttonShader.h"

/**
 *	Constructor.
 */
Button::Button(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	this->x1 = calculateXCoordinate(x1); this->y1 = calculateYCoordinate(y1);
	this->x2 = calculateXCoordinate(x2); this->y2 = calculateYCoordinate(y2);
	this->x3 = calculateXCoordinate(x3); this->y3 = calculateYCoordinate(y3);
	this->x4 = calculateXCoordinate(x4); this->y4 = calculateYCoordinate(y4);

	shader = CompileShader(buttonVertexShaderSrc, buttonFragmentShaderSrc, "");

	createRect();
}

/**
 *	Deconstructor.
 */
Button::~Button() {

}

/**
 *	Create a rectangle.
 */
void Button::createRect() {
	vertices.push_back(x1); vertices.push_back(y1);		// Top left corner
	vertices.push_back(x2); vertices.push_back(y2);		// Bottom left corner
	vertices.push_back(x3); vertices.push_back(y3);		// Bottom right corner
	vertices.push_back(x4); vertices.push_back(y4);		// Top right corner

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(), &(indices[0]), GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (const void*)0);
}

/**
 *	Draw the button on the screen.
 */
void Button::draw() {
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}