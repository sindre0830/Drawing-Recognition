#ifndef CLASS_SHADER_POINTSHADER_H_
#define CLASS_SHADER_POINTSHADER_H_
/* external libraries */
#include <string>

static const std::string pointVertexShaderSrc = R"(
#version 430 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

// Outputs
out vec3 vsColor;

void main() {
	// Pass color to fragment shader
	vsColor = aColor;

	// Set position
	gl_Position = vec4(aPosition, 1.0f, 1.0f);
}
	
)";

static const std::string pointFragmentShaderSrc = R"(
#version 430 core

/** Inputs */
in vec3 vsColor;

/** Outputs */
out vec4 outColor;

void main() 
{
	outColor = vec4(vsColor, 1.0f);
}
)";

#endif // CLASS_SHADER_POINTSHADER_H_
