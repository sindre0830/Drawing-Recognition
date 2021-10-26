#include "Paintbrush.h"
#include "functions.h"
#include "shaders/shader.h"

#include <iostream>

/**
 *	Constructor.
 */
Paintbrush::Paintbrush() {
	indices_lastIndex = 0;
	vao = vbo = ebo = 0;
	shader = CompileShader(pointVertexShaderSrc, pointFragmentShaderSrc, "");
}

/**
 *	Deconstructor.
 */
Paintbrush::~Paintbrush() {
	while (!points.empty()) {
		auto it = points.begin();
		delete *it;
		points.erase(it);
	}
}

/**
 *	Generate and bind buffers the first time a point is created.
 */
void Paintbrush::init() {
	float x = points[0]->getX(), y = points[0]->getY();
	float size = points[0]->getSize();

	// Bottom left corner
	vertices.push_back(x - size);
	vertices.push_back(y - size);

	// Top left corner
	vertices.push_back(x - size);
	vertices.push_back(y + size);

	// Top right corner
	vertices.push_back(x + size);
	vertices.push_back(y + size);

	// Bottom right corner
	vertices.push_back(x + size);
	vertices.push_back(y - size);

	indices.push_back(indices_lastIndex);
	indices.push_back(indices_lastIndex + 1);
	indices.push_back(indices_lastIndex + 2);

	indices.push_back(indices_lastIndex);
	indices.push_back(indices_lastIndex + 2);
	indices.push_back(indices_lastIndex + 3);

	indices_lastIndex += 4;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (const void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(), &(indices[0]), GL_STATIC_DRAW);
}

/** 
 *	Create a point.
 */
void Paintbrush::createPoint(double x, double y) {
	// Cast to float 
	float xf = x, yf = y;

	Point* point = new Point(calculateXCoordinate(x), calculateYCoordinate(y), 1.f);
	points.push_back(point);

	// Generate buffers if this is the first point in the vector
	if (points.size() == 1) init();
	else addPoint(point);
}

/** 
 *	Add points' vertices and indices to vectors.
 */
void Paintbrush::addPoint(Point* point) {

}

void Paintbrush::draw() {
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6 * points.size(), GL_UNSIGNED_INT, 0);
}
