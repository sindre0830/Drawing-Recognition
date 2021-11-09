#ifndef PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_FUNCTIONS_H_
#define PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_FUNCTIONS_H_

#include <glad/glad.h>
#include <string>

float calculateXCoordinate(float x);
float calculateYCoordinate(float y);

GLuint CompileShader(const std::string& vertexShaderSrc,
                     const std::string& fragmentShaderSrc,
                     const std::string& geometryShaderSrc/*=""*/);

#endif  // PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_FUNCTIONS_H_
