/**
 * @file functions.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
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
    word,
    game,
    none
};

float calculateXCoordinate(float x);
float calculateYCoordinate(float y);

GLuint CompileShader(const std::string& vertexShaderSrc,
                     const std::string& fragmentShaderSrc,
                     const std::string& geometryShaderSrc/*=""*/);

#endif  // FUNCTIONS_H_
