/**
 * @file Button.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_BUTTON_H_
#define CLASS_HEADER_BUTTON_H_

/* external libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/* local libraries */
#include "../../Header/dictionary.h"

struct Rect {
    float x1, y1,
          x2, y2,
          x3, y3,
          x4, y4;
};

/**
 *	Class for creating and interacting with buttons.
 */
class Button {
 private:
    Rect rect;
    Color color;

    GLuint vao, vbo, ebo, shader;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    glm::mat4 projection;
 public:
    Button() {}
    Button(Rect rect, Color color);
    ~Button();

    Rect getRect() { return rect; }
    Color getColor() { return color; }

    void createRect();
    void draw();
    bool detectClick(double x, double y);
};

#endif  // CLASS_HEADER_BUTTON_H_
