/**
 * @file Button.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/button.h"
/* local libraries */
#include "../Header/functionality.h"
#include "./Shader/buttonShader.h"

/**
 *	Constructor.
 * 
 *	@param rect - The area of the button
 *	@param color - The color of the button
 */
Button::Button(Rect rect, Color color) {
    this->rect = rect;
    this->color = color;
    shader = compileShader(buttonVertexShaderSrc, buttonFragmentShaderSrc);

    projection = glm::ortho(
        0.0f,
        static_cast<float>(WINDOW_WIDTH),
        0.0f,
        static_cast<float>(WINDOW_HEIGHT));
    createRect();
}

/**
 *	Deconstructor.
 */
Button::~Button() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader);
}

/**
 *	Create a rectangle.
 */
void Button::createRect() {
    RGB rgb = colors.find(color)->second;
    float r = rgb.r, g = rgb.g, b = rgb.b;
    // top left corner
    vertices.push_back(rect.x1);
    vertices.push_back(rect.y1);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);
    // bottom left corner
    vertices.push_back(rect.x2);
    vertices.push_back(rect.y2);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);
    // bottom right corner
    vertices.push_back(rect.x3);
    vertices.push_back(rect.y3);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);
    // top right corner
    vertices.push_back(rect.x4);
    vertices.push_back(rect.y4);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);

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
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(std::vector<GLfloat>) + sizeof(GLfloat) * vertices.size(),
        &(vertices[0]), GL_STATIC_DRAW);

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
        (const void*)(sizeof(GLfloat) * 2));
}

/**
 *	Draw the button on the screen.
 */
void Button::draw() {
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(
        shader,
        "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

/**
 *	Detects button click.
 *	
 *	@param x - The mouse's x position
 *	@param y - The mouse's y position
 */
bool Button::detectClick(double x, double y) {
    float xf = x,
          yf = 900 - y;

    // Checks if the coordinates are in the range of the rectangle
    if (xf >= rect.x1 && xf <= rect.x4 && yf <= rect.y1 && yf >= rect.y2) {
        return true;
    }

    return false;
}
