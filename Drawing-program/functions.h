#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include <string>

float calculateXCoordinate(float x);
float calculateYCoordinate(float y);

GLuint CompileShader(const std::string& vertexShaderSrc,
                     const std::string& fragmentShaderSrc,
                     const std::string& geometryShaderSrc/*=""*/);

#endif // !__FUNCTIONS_H


