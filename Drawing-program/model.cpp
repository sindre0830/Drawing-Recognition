#include "model.h"
/* external libraries */
#include <iostream>
#include <Python.h>

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

void Model::predict(int* data[4 * 128 * 128]) {
    return;
}
