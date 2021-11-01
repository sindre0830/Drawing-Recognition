#ifndef __BUTTONSHADER_H
#define __BUTTONSHADER_H

#include <string>

static const std::string buttonVertexShaderSrc = R"(
#version 430 core
layout(location = 0) in vec2 aPosition;
//layout(location = 1) in vec3 aColor;

// Outputs
//out vec3 vsColor;

void main() {
	// Pass color to fragment shader
	//vsColor = aColor;

	// Set position
	gl_Position = vec4(aPosition, 1.0f, 1.0f);
}
	
)";

static const std::string buttonFragmentShaderSrc = R"(
#version 430 core

/** Inputs */
//in vec3 vsColor;

/** Outputs */
out vec4 outColor;

void main() 
{
	outColor = vec4(1.0f, 0.f, 0.f, 1.0f);
}
)";

#endif // !__SHADER_H