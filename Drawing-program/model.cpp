#include "model.h"
/* local libraries */
#include "const.h"
/* external libraries */
#include <filesystem>
#include <iostream>
#include <Python.h>
#include "external/stb_image_write.h"
#include <GLFW/glfw3.h>

Model::Model() {
	std::cout << "Python Version: " << PY_VERSION << std::endl;
}

Model::~Model() {
}

void initPythonScript(std::string filename) {
    Py_Initialize();
    PyRun_SimpleString(("exec(open(\"" + filename + "\").read())").c_str());
    Py_Finalize();
}

void Model::predict(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	std::filesystem::create_directories("../Data");
	GLubyte* pixels = new GLubyte[3 * WINDOW_WIDTH * WINDOW_HEIGHT];

	// Read screen pixels
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	stbi_flip_vertically_on_write(true);

	// Save to file
	stbi_write_jpg("../Data/test.jpg", WINDOW_WIDTH, WINDOW_HEIGHT, 3, pixels, 100);

	delete[] pixels;
}
