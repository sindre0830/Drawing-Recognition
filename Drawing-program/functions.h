/**
 * @file functions.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

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

#endif  // FUNCTIONS_H_
