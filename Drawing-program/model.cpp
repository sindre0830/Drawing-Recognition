#include "model.h"
/* external libraries */
#include <iostream>

Model::Model() {
}

Model::~Model() {
}

int Model::init() {
	std::cout << "TensorFlow Version: " << mlpack::util::GetVersion() << std::endl;
    return EXIT_SUCCESS;
}

void Model::predict(int* data[4 * 128 * 128]) {
    return;
}
