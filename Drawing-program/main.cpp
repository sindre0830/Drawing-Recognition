#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "const.h"
#include "functions.h"
#include "Paintbrush/Paintbrush.h"

#include <vector>
#include <iostream>

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

	Paintbrush* paintbrush = new Paintbrush();

	double x, y;	// Mouse position

	float t = 0.f; // Total time elapsed since start of program

	while (!glfwWindowShouldClose(window)) {
		// Time management
		float dt = glfwGetTime() - t;
		t += dt;

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Get mouse position
			glfwGetCursorPos(window, &x, &y);

			// Create point on mouse position
			paintbrush->createPoint(x, y);
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			paintbrush->setNewPos(true);
		}

		paintbrush->draw();

		glfwSwapBuffers(window);

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




