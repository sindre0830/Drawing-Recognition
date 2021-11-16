/**
 * @file Button.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef NAVIGATION_BUTTON_H_
#define NAVIGATION_BUTTON_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../Colors.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    glm::mat4 projection;
 public:
    Button() {}
    Button(Rect rect, Color color, ButtonType type);
    ~Button();

    void createRect();
    void draw();
    bool detectClick(double x, double y);
};

#endif  // NAVIGATION_BUTTON_H_
