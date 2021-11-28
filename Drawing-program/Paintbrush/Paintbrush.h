/**
 * @file Paintbrush.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef PAINTBRUSH_PAINTBRUSH_H_
#define PAINTBRUSH_PAINTBRUSH_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <utility>
#include "../Colors.h"

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

#endif  // PAINTBRUSH_PAINTBRUSH_H_
