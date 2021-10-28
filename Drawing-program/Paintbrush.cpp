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
		delete* it;
		points.erase(it);
	}

	//glDeleteShaderProgram(shader);
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

	Point* point = new Point(calculateXCoordinate(xf), calculateYCoordinate(yf), 0.05f);
	points.push_back(point);

	// Generate buffers if this is the first point in the vector
	if (points.size() == 1) init();
	else createLine();
}

/**
 *	Add points' vertices and indices to vectors.
 */
void Paintbrush::createLine() {
	// Create help variables
	int pointsSize = points.size();

	// Get all involved points and their attributes
	Point* newPoint = points[pointsSize - 1];
	//float r = newPoint->getR(), g = newPoint->getG(), b = newPoint->getB();
	float newPointSize = newPoint->getSize();

	Point* prevPoint = points[pointsSize - 2];
	//float pR = prevPoint->getR(), pG = prevPoint->getG(), pB = prevPoint->getB();
	float prevPointSize = newPoint->getSize();

	// Create a vector from the previous point to the newest
	std::pair<float, float> v = {
		newPoint->getX() - prevPoint->getX(),
		newPoint->getY() - prevPoint->getY()
	};

	// Normalize 
	float v1 = sqrt(pow(v.first, 2) + pow(v.second, 2));
	v.first /= v1; v.second /= v1;

	// Find the orthagonal 
	std::pair<float, float> orth = {
		v.second,
		-v.first
	};

	// Push starting points (L and R)
	vertices.push_back(prevPoint->getX() - orth.first * prevPointSize);
	vertices.push_back(prevPoint->getY() - orth.second * prevPointSize);
	//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

	vertices.push_back(prevPoint->getX() + orth.first * prevPointSize);
	vertices.push_back(prevPoint->getY() + orth.second * prevPointSize);
	//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

	// Push ending points (L and R)
	vertices.push_back(newPoint->getX() + orth.first * newPointSize);
	vertices.push_back(newPoint->getY() + orth.second * newPointSize);
	//vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

	vertices.push_back(newPoint->getX() - orth.first * newPointSize);
	vertices.push_back(newPoint->getY() - orth.second * newPointSize);
	//vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

	indices.push_back(indices_lastIndex);
	indices.push_back(indices_lastIndex + 1);
	indices.push_back(indices_lastIndex + 2);

	indices.push_back(indices_lastIndex);
	indices.push_back(indices_lastIndex + 2);
	indices.push_back(indices_lastIndex + 3);

	indices_lastIndex += 4;

	// Create filler triangles so the lines looks connected
	if (points.size() > 2) {
		// The third last point, part of the line to connect this line with
		Point* prev2Point = points[points.size() - 3];

		// Vector between third last point and second last point
		v = {
			prevPoint->getX() - prev2Point->getX(),
			prevPoint->getY() - prev2Point->getY()
		};

		// Normalize 
		float v1 = sqrt(pow(v.first, 2) + pow(v.second, 2));
		v.first /= v1; v.second /= v1;

		// Find the orthagonal 
		std::pair<float, float> orth2 = {
			v.second,
			-v.first
		};

		// Push back filler triangles
		vertices.push_back(prevPoint->getX());
		vertices.push_back(prevPoint->getY());
		//vertices.push_back(); vertices.push_back(pG); vertices.push_back(pB);

		vertices.push_back(prevPoint->getX() + orth2.first * prevPoint->getSize());
		vertices.push_back(prevPoint->getY() + orth2.second * prevPoint->getSize());
		//vertices.push_back(0); vertices.push_back(0); vertices.push_back(1);

		vertices.push_back(prevPoint->getX() + orth.first * prevPoint->getSize());
		vertices.push_back(prevPoint->getY() + orth.second * prevPoint->getSize());
		//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

		vertices.push_back(prevPoint->getX());
		vertices.push_back(prevPoint->getY());
		//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

		vertices.push_back(prevPoint->getX() - orth2.first * prevPoint->getSize());
		vertices.push_back(prevPoint->getY() - orth2.second * prevPoint->getSize());
		//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

		vertices.push_back(prevPoint->getX() - orth.first * prevPoint->getSize());
		vertices.push_back(prevPoint->getY() - orth.second * prevPoint->getSize());
		//vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);


		// ... And their corresponding indices
		indices.push_back(indices_lastIndex);
		indices.push_back(indices_lastIndex + 1);
		indices.push_back(indices_lastIndex + 2);

		indices.push_back(indices_lastIndex + 3);
		indices.push_back(indices_lastIndex + 4);
		indices.push_back(indices_lastIndex + 5);

		indices_lastIndex += 6;
	}

	// Lastly, update buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(), &(indices[0]), GL_STATIC_DRAW);
}

void Paintbrush::draw() {
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
