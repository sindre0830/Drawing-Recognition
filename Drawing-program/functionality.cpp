/**
 * @file functions.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/functionality.h"
/* external libraries */
#include <GLFW/glfw3.h>
#include <iostream>
/* local libraries */
#include "./Header/dictionary.h"

/**
 *  Transforms x coordinate.
 * 
 *  @param x - The coordinate to change
 *  @return The new x value
 */
float calculateXCoordinate(float x) {
    return (x / WINDOW_WIDTH - 0.5f) * 2.f;
}

/**
 *  Transforms y coordinate.
 *
 *  @param y - The coordinate to change
 *  @return The new y value
 */
float calculateYCoordinate(float y) {
    return -(y / WINDOW_HEIGHT - 0.5f) * 2.f;
}

/**
 *  Compiles shader.
 * 
 *  @param vertexShaderSrc - The source code for the vertex shader
 *  @param fragmentShaderSrc - The source code of the fragment shader
 *  @return The shader program
 */
GLuint compileShader(const std::string& vertexShaderSrc,
                     const std::string& fragmentShaderSrc) {
    // Get the vertex and fragment shader source
    const char* vertexSrc = vertexShaderSrc.c_str();
    const char* fragmentSrc = fragmentShaderSrc.c_str();

    // Create the program
    GLuint program = glCreateProgram();

    // Compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    GLchar* infoLog = new char[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: VERTEX" << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
        return EXIT_FAILURE;
    }

    // Compile the fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: FRAGMENT" << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
        return EXIT_FAILURE;
    }

    // Attach the shaders to the program and link
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // The shaders are not necessary anymore, so they can be deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
