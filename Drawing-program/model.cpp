#include "model.h"
/* local libraries */
#include "const.h"
/* external libraries */
#include <filesystem>
#include <iostream>
#include <Python.h>
#include <FreeImage.h>
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

void Model::predict() {
    std::cout << "oi" << std::endl;
    std::filesystem::create_directories("../Data");

    BYTE* pixels = new BYTE[3 * WINDOW_WIDTH * WINDOW_HEIGHT];
    glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGR, GL_UNSIGNED_BYTE, pixels);

    FIBITMAP* image = FreeImage_ConvertFromRawBits(
        pixels,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        3 * WINDOW_WIDTH,
        24,
        0x0000FF,
        0x00FF00,
        0xFF0000,
        false
    );
    FreeImage_Save(FIF_BMP, image, "../Data/tmp.png", 0);

    FreeImage_Unload(image);
    delete[] pixels;
}
