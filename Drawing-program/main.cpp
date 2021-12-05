/**
 * @file main.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

/* external libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <thread>  // NOLINT(build/c++11)
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/* local libraries */
#include "./Class/Header/model.h"
#include "./Class/Header/sceneManager.h"

/**
 * Main program.
 */
int main() {
    // initialize glfw
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed.\n";
        std::cin.get();
        return EXIT_FAILURE;
    }
    // initialize model and python script
    Model* model = new Model();
    std::thread t1(&Model::initScript, model);
    // set window hints
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Drawing Recognition", NULL, NULL);
    // branch if window isn't created and kill the application
    if (window == nullptr) {
        std::cerr << "GLFW failed on window creation.\n";
        std::cin.get();
        glfwTerminate();
        model->terminate();
        t1.join();
        return EXIT_FAILURE;
    }
    // set the OpenGL context to the window
    glfwMakeContextCurrent(window);
    // load glad configurations for OpenGL
    if (!gladLoadGL()) {
        std::cerr << "Glad initialization failed.\n";
        std::cin.get();
        glfwTerminate();
        model->terminate();
        t1.join();
        return EXIT_FAILURE;
    }
    // enable transparency on texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // set background color white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // construct scene manager object
    SceneManager* scenes = new SceneManager();
    // setup timer
    static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime, deltaTime = 0;
    int countdown = 60, predictionTimer = 0;
    // setup model prediction (takes 2 seconds)
    model->predict(window);
    // loop until user closes window
    while (!glfwWindowShouldClose(window)) {
        // delta time managment
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;
        // processes all pending events
        glfwPollEvents();
        // for every frame reset background color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        // draw scene
        scenes->draw(window, model->prediction, countdown);
        // reset countdown if the current round has ended
        if (scenes->getCurrentScene() != game && scenes->gameStarted) {
            countdown = 60;
            scenes->gameStarted = false;
        }
        // branch if there has been one second since game loop started
        if (glfwGetTime() - timer > 1.0f) {
            timer++;
            predictionTimer++;
            // branch if game scene is active and decrease counter
            if (scenes->gameStarted) countdown--;
            // branch if there has been two seconds since game loop started
            if (predictionTimer >= 2 && scenes->gameStarted) {
                model->predict(window);
                predictionTimer = 0;
            }
        }
        // reset delta time
        if (deltaTime >= 1.0) deltaTime -= 1.0;
        // go to next buffer
        glfwSwapBuffers(window);
        // break loop if exit button is pressed
        if (scenes->getCurrentScene() == exitGame) break;
    }
    // clear memory before ending program
    glUseProgram(0);
    delete scenes;
    glfwDestroyWindow(window);
    glfwTerminate();
    model->terminate();
    t1.join();
    delete model;
}
