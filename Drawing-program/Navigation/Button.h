#ifndef NAVIGATION_BUTTON_H_
#define NAVIGATION_BUTTON_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../Colors.h"

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
    Button() {}
    Button(Rect rect, Color color, ButtonType type);
    ~Button();

    void createRect();
    void draw();
    bool detectClick(double x, double y);
};

#endif  // NAVIGATION_BUTTON_H_
