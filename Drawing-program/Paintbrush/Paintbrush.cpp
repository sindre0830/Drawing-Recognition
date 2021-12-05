/**
 * @file Paintbrush.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "Paintbrush.h"
#include <cmath>
#include <utility>
#include "../functions.h"
#include "../shaders/pointShader.h"

/**
 *	Constructor.
 */
Paintbrush::Paintbrush() {
    indices_lastIndex = 0;
    newPos = true;
    vao = vbo = ebo = 0;
    shader = compileShader(pointVertexShaderSrc, pointFragmentShaderSrc);
    size = 0.01f;
    color = black;
}

/**
 *	Deconstructor.
 */
Paintbrush::~Paintbrush() {
    clearPoints();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader);
}

/**
 *	Generate and bind buffers the first time a point is created.
 */
void Paintbrush::init() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(),
        &(vertices[0]),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(),
        &(indices[0]),
        GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 5, (const void*)0);

    // Color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 5,
        (const void*)(sizeof(GL_FLOAT) * 2));
}

/**
 *	Create either the very first position, or the first position after the mouse button is released.
 */
void Paintbrush::createFirstPos() {
    Point point = points[points.size() - 1];
    float x = point.x, y = point.y;
    float size = point.size;
    float r = point.r, g = point.g, b = point.b;

    // Bottom left corner
    vertices.push_back(x - size);
    vertices.push_back(y - size);
    vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

    // Top left corner
    vertices.push_back(x - size);
    vertices.push_back(y + size);
    vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

    // Top right corner
    vertices.push_back(x + size);
    vertices.push_back(y + size);
    vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

    // Bottom right corner
    vertices.push_back(x + size);
    vertices.push_back(y - size);
    vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);

    indices.push_back(indices_lastIndex);
    indices.push_back(indices_lastIndex + 1);
    indices.push_back(indices_lastIndex + 2);

    indices.push_back(indices_lastIndex);
    indices.push_back(indices_lastIndex + 2);
    indices.push_back(indices_lastIndex + 3);

    indices_lastIndex += 4;

    newPos = false;

    if (points.size() == 1) {
        init();
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(),
            &(vertices[0]),
            GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(),
            &(indices[0]),
            GL_STATIC_DRAW);
    }
}

/**
 *	Create a point.
 * 
 *	@param x - The point's x coordinate
 *	@param y - The point's y coordinate
 *	@see calculateXCoordinate(...)
 *	@see calculateYCoordinate(...)
 *	@see Paintbrush::createFirstPos()
 *	@see Paintbrush::createLine()
 */
void Paintbrush::createPoint(double x, double y) {
    // Cast to float
    float xf = x, yf = y;
    RGB rgb = findColor(color);

    Point point = {
        calculateXCoordinate(xf),
        calculateYCoordinate(yf),
        rgb.r, rgb.g, rgb.b,
        size
    };

    points.push_back(point);

    // Generate buffers if this is the first point in the vector
    if (newPos) {
        createFirstPos();
    } else {
        createLine();
    }
}

/**
 *	Add points' vertices and indices to vectors.
 * 
 *	@see Paintbrush::findOrthogonal(...)
 */
void Paintbrush::createLine() {
    // Create help variables
    int pointsSize = points.size();

    // Get all involved points and their attributes
    Point newPoint = points[pointsSize - 1];
    float nR = newPoint.r, nG = newPoint.g, nB = newPoint.b;
    float newPointSize = newPoint.size;

    Point prevPoint = points[pointsSize - 2];
    float pR = prevPoint.r, pG = prevPoint.g, pB = prevPoint.b;
    float prevPointSize = newPoint.size;

    // Create a vector from the previous point to the newest
    std::pair<float, float> orth = findOrthogonal(newPoint, prevPoint);

    // Push starting points (L and R)
    vertices.push_back(prevPoint.x - orth.first * prevPointSize);
    vertices.push_back(prevPoint.y - orth.second * prevPointSize);
    vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

    vertices.push_back(prevPoint.x + orth.first * prevPointSize);
    vertices.push_back(prevPoint.y + orth.second * prevPointSize);
    vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

    // Push ending points (L and R)
    vertices.push_back(newPoint.x + orth.first * newPointSize);
    vertices.push_back(newPoint.y + orth.second * newPointSize);
    vertices.push_back(nR); vertices.push_back(nG); vertices.push_back(nB);

    vertices.push_back(newPoint.x - orth.first * newPointSize);
    vertices.push_back(newPoint.y - orth.second * newPointSize);
    vertices.push_back(nR); vertices.push_back(nG); vertices.push_back(nB);

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
        Point prev2Point = points[points.size() - 3];

        std::pair<float, float> orth2 = findOrthogonal(prevPoint, prev2Point);

        // Push back filler triangles
        vertices.push_back(prevPoint.x);
        vertices.push_back(prevPoint.y);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        vertices.push_back(prevPoint.x + orth2.first * prevPoint.size);
        vertices.push_back(prevPoint.y + orth2.second * prevPoint.size);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        vertices.push_back(prevPoint.x + orth.first * prevPoint.size);
        vertices.push_back(prevPoint.y + orth.second * prevPoint.size);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        vertices.push_back(prevPoint.x);
        vertices.push_back(prevPoint.y);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        vertices.push_back(prevPoint.x - orth2.first * prevPoint.size);
        vertices.push_back(prevPoint.y - orth2.second * prevPoint.size);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        vertices.push_back(prevPoint.x - orth.first * prevPoint.size);
        vertices.push_back(prevPoint.y - orth.second * prevPoint.size);
        vertices.push_back(pR); vertices.push_back(pG); vertices.push_back(pB);

        // Their corresponding indices
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
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(),
        &(vertices[0]),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(std::vector<GLuint>) + sizeof(GLuint) * indices.size(),
        &(indices[0]),
        GL_STATIC_DRAW);
}

/**
 *	Create a vector between two points and finds its orthogonal.
 * 
 *	@param point1 - The first point
 *	@param point2 - The second point
 *	@return The orthogonal
 */
std::pair<float, float> Paintbrush::findOrthogonal(Point point1, Point point2) {
    // Vector between third last point and second last point
    std::pair<float, float> v = {
        point1.x - point2.x,
        point1.y - point2.y
    };

    // Normalize
    float v1 = sqrt(pow(v.first, 2) + pow(v.second, 2));
    v.first /= v1; v.second /= v1;

    // Find the orthogonal
    std::pair<float, float> orth = {
        v.second,
        -v.first
    };

    return orth;
}

/**
 *	Draw the lines on screen.
 */
void Paintbrush::draw() {
    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

/**
 *  Clear all points.
 */
void Paintbrush::clearPoints() {
    points.clear();
    vertices.clear();
    indices.clear();
    indices_lastIndex = 0;
    newPos = true;
}
