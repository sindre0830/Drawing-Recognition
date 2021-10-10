#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

#include <iostream>

int main() {
	// Initialize glfw
	glfwInit();

	// Tell which version is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	int windowWidth = 800;
	int windowHeight = 800;

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Drawing Recognition", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Load glad configurations for OpenGL
	gladLoadGL();

	// Change background color
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// The area to be rendered. Bottom left corner (0, 0) to top tight (windowWidth, windowHeight)
	glViewport(0, 0, windowWidth, windowHeight);
	

	// Main loop that runs until a stop condition is reached
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}