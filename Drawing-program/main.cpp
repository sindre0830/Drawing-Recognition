#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "const.h"

#include <vector>
#include <iostream>

// Function headers
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main() {
	// Initialize glfw
	glfwInit();

	// Tell which version is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Drawing Recognition", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Load glad configurations for OpenGL
	gladLoadGL();

	// Change background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	float t = 0.f; // Total time elapsed since start of program

	while (!glfwWindowShouldClose(window)) {
		// time
		float dt = glfwGetTime() - t;
		t += dt;

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);

		glfwSetMouseButtonCallback(window, mouse_button_callback);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			break;
		}

		// Limit to 30 fps
		while (glfwGetTime() < t + 1.0 / 30) {
		}
	}

	glUseProgram(0);

	glfwDestroyWindow(window);
	glfwTerminate();
}

// *************************************************************************************
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double x, y;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &x, &y);

		std::cout << "\nx: " << x << " - y: " << y;
	}
}



