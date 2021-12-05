/**
 * @file model.cpp
 * @author Sindre Eiklid
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */
#include "model.h"
/* external libraries */
#include <Python.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include <string>
/* local libraries */
#include "const.h"
#include "external/stb_image_write.h"
#include "external/zmq.hpp"

Model::Model() {
    std::cout << "Python Version: " << PY_VERSION << std::endl;
    filename = "../predict.py";
    prediction = "Unknown";
}

Model::~Model() {}

void Model::initScript() {
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

    ping("do something...");
}

void Model::ping(const std::string cmd) {
    // setup connection
    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, zmq::socket_type::req);
    sock.connect("tcp://localhost:5959");
    // ping server
    sock.send(zmq::buffer(cmd), zmq::send_flags::dontwait);
    // get prediction
    zmq::message_t msg;
    sock.recv(msg);
    prediction = msg.to_string();
}

void Model::terminate() {
    ping("terminate");
}
