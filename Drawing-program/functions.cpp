/**
 * @file functions.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "functions.h"

#include <GLFW/glfw3.h>
#include <iostream>

/**
 *  Transforms x coordinate.
 * 
 *  @param x - The coordinate to change
 *  @return The new x value
 */
float calculateXCoordinate(float x) {
    return (x / glfwGetVideoMode(glfwGetPrimaryMonitor())->width - 0.5f) * 2.f;
}

/**
 *  Transforms y coordinate.
 *
 *  @param y - The coordinate to change
 *  @return The new y value
 */
float calculateYCoordinate(float y) {
    return -(y / glfwGetVideoMode(glfwGetPrimaryMonitor())->height - 0.5f) * 2.f;
}

GLuint CompileShader(const std::string& vertexShaderSrc,
    const std::string& fragmentShaderSrc,
    const std::string& geometryShaderSrc/*=""*/) {

    auto vertexSrc = vertexShaderSrc.c_str();
    auto fragmentSrc = fragmentShaderSrc.c_str();
    auto geometrySrc = geometryShaderSrc.c_str();

    // Create program
    auto shaderProgram = glCreateProgram();

    // Vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    int bufflen;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &bufflen);
    if (bufflen > 1) {
        GLchar* log_string = new char[bufflen + 1];
        glGetShaderInfoLog(vertexShader, bufflen, 0, log_string);

        std::cerr << log_string << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }

    glAttachShader(shaderProgram, vertexShader);

    // Geometry shader (if there is any)
    auto geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    if (geometryShaderSrc != "") {
        glShaderSource(geometryShader, 1, &geometrySrc, nullptr);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &bufflen);
        if (bufflen > 1) {
            GLchar* log_string = new char[bufflen + 1];
            glGetShaderInfoLog(geometryShader, bufflen, 0, log_string);

            std::cerr << log_string << std::endl;
            std::cin.get();
            return EXIT_FAILURE;
        }

        glAttachShader(shaderProgram, geometryShader);
    }

    // Fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &bufflen);
    if (bufflen > 1) {
        GLchar* log_string = new char[bufflen + 1];
        glGetShaderInfoLog(fragmentShader, bufflen, 0, log_string);

        std::cerr << log_string << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }

    glAttachShader(shaderProgram, fragmentShader);

    // Link
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);

    return shaderProgram;
}
