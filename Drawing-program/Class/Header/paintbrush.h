/**
 * @file Paintbrush.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_PAINTBRUSH_H_
#define CLASS_HEADER_PAINTBRUSH_H_

/* external libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <utility>
/* local libraries */
#include "../../Header/dictionary.h"

/**
 *  Struct for storing a point's attributes.
 */
struct Point {
    float x, y,
          r, g, b,
          size;
};

/**
 *	Class for controlling points.
 */
class Paintbrush {
 private:
    std::vector<Point> points;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    GLuint vao, vbo, ebo, shader;
    int indices_lastIndex;
    bool newPos;

    float size;
    Color color;

 public:
    Paintbrush();
    ~Paintbrush();

    std::vector<Point> getPoints() { return points; }
    void setNewPos(bool newPos) { this->newPos = newPos; }
    void setNewColor(Color color) { this->color = color; }

    void init();
    void createPoint(double x, double y);
    void createFirstPos();
    void createLine();
    std::pair<float, float> findOrthogonal(Point point1, Point point2);
    void draw();
    void clearPoints();
};

#endif  // CLASS_HEADER_PAINTBRUSH_H_
