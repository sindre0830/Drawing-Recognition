/**
 * @file functions.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef HEADER_FUNCTIONALITY_H_
#define HEADER_FUNCTIONALITY_H_

/* external libraries */
#include <glad/glad.h>
#include <string>

enum SceneType {
    menu,
    about,
    game,
    end,
    exitGame,
    none
};

float calculateXCoordinate(float x);
float calculateYCoordinate(float y);

GLuint compileShader(const std::string& vertexShaderSrc,
                     const std::string& fragmentShaderSrc);

#endif  // HEADER_FUNCTIONALITY_H_
