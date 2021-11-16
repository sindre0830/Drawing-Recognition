#include "model.h"
/* external libraries */
#include <iostream>
#include <Python.h>

Model::Model() {
}

Model::~Model() {
}

int Model::init() {
	std::cout << "Python Version: " << PY_VERSION << std::endl;
    Py_Initialize();
    PyRun_SimpleString("exec(open(\"../predict.py\").read())");
    Py_Finalize();
    return EXIT_SUCCESS;
}

void Model::predict(int* data[4 * 128 * 128]) {
    return;
}
