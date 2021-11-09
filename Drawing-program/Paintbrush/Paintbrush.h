#ifndef PAINTBRUSH_PAINTBRUSH_H_
#define PAINTBRUSH_PAINTBRUSH_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <utility>
#include "Point.h"
#include "../Colors.h"


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
    bool newPos;

    float size;
    Color color;

 public:
    Paintbrush();
    ~Paintbrush();

    std::vector<Point*> getPoints() { return points; }
    int getPointsSize() { return points.size(); }
    void setNewPos(bool newPos) { this->newPos = newPos; }
    void setNewColor(Color color) { this->color = color; }

    void init();
    void createPoint(double x, double y);
    void createFirstPos();
    void createLine();
    std::pair<float, float> findOrthogonal(Point* point1, Point* point2);
    void draw();
};

#endif  // PAINTBRUSH_PAINTBRUSH_H_
