/**
 * @file main.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "./const.h"
#include "Scenes/SceneManager.h"

int main() {
    // Initialize glfw
    if (!glfwInit()) {
        std::cerr << "Initialization of GLFW failed.";
        std::cin.get();
        return EXIT_FAILURE;
    }

    // Set window hints
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Drawing Recognition", NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Window creation failed";
        std::cin.get();
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    // Load glad configurations for OpenGL
    if (!gladLoadGL()) {
        std::cerr << "Initialization of Glad failed.";
        std::cin.get();
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Enable blend so text is text
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Change background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initColors();

    SceneManager* scenes = new SceneManager();

    float t = 0.f;  // Total time elapsed since start of program

    std::string guessedWord = "sTRAWberry";

    // setup timer
    static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime, deltaTime = 0;
    int countdown = 60;

    while (!glfwWindowShouldClose(window)) {
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        scenes->draw(window, guessedWord, countdown);

        glfwSwapBuffers(window);

        // Exit the game
        if (scenes->getCurrentScene() == exitGame) break;

        // branch if there has been two second since game loop started
        if (glfwGetTime() - timer > 1.0f) {
            timer += 1;
            if (scenes->gameStarted) countdown--;
        }

        // reset delta time
        if (deltaTime >= 1.0) deltaTime -= 1.0;

        // Reset countdown if the current round has ended
        if (scenes->getCurrentScene() != game && scenes->gameStarted) {
            countdown = 60;
            scenes->gameStarted = false;
        }

        // Limit to 60 fps
        while (glfwGetTime() < t + 1.0 / 60) {
        }
    }

    glUseProgram(0);

    delete scenes;
    glfwDestroyWindow(window);
    glfwTerminate();
}
