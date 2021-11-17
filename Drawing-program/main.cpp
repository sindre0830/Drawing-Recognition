#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "const.h"
#include "functions.h"
#include "Paintbrush/Paintbrush.h"
#include "Colors.h"
#include "model.h"
#include "external/stb_image_write.h"

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <filesystem>

int main() {
	// initialize model
	Model* model = new Model();
	std::thread t1(initPythonScript, "../predict.py");

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

	std::cout << "\n\tChange color: "
			  << "\n\t\ta - black"
			  << "\n\t\tr - red"
			  << "\n\t\tg - green"
			  << "\n\t\tb - blue\n";

	glfwMakeContextCurrent(window);

	// Load glad configurations for OpenGL
	gladLoadGL();

	// Change background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	initColors();

	glm::ortho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	Paintbrush* paintbrush = new Paintbrush();

	double x, y;	// Mouse position

	float t = 0.f; // Total time elapsed since start of program

	// setup timer
	static double limitFPS = 1.0 / 60.0;
	double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime, deltaTime = 0; 

	while (!glfwWindowShouldClose(window)) {
		// Time management
		float dt = glfwGetTime() - t;
		t += dt;

		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

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

		// Change of colors, by pressing keys
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) paintbrush->setNewColor(black);
		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) paintbrush->setNewColor(red);
		else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) paintbrush->setNewColor(green);
		else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) paintbrush->setNewColor(blue);
		else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

		// branch if there has been one second since game loop started
		if (glfwGetTime() - timer > 1.0f) {
			model->predict(window);
			timer++;
		}
		// reset delta time 
		if(deltaTime >= 1.0) deltaTime -= 1.0;
	
		// Limit to 60 fps
		while (glfwGetTime() < t + 1.0 / 60) {
		}
	}

	glUseProgram(0);

	glfwDestroyWindow(window);
	glfwTerminate();
}


