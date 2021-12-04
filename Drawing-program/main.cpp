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
#include <iostream>
#include "Scenes/SceneManager.h"

int main() {
    // Initialize glfw
    glfwInit();

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(800, 900, "Drawing Recognition", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Load glad configurations for OpenGL
    gladLoadGL();

    // Enable blend so text is text
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Change background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initColors();

    SceneManager* scenes = new SceneManager();

    float t = 0.f;  // Total time elapsed since start of program

    std::string guessedWord = "strawberry";

    while (!glfwWindowShouldClose(window)) {
        // Time management
        float dt = glfwGetTime() - t;
        t += dt;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        scenes->draw(window, guessedWord);

        glfwSwapBuffers(window);

        // Exit the game
        if (scenes->getCurrentScene() == exitGame) break;

        // Limit to 60 fps
        while (glfwGetTime() < t + 1.0 / 60) {
        }
    }

    glUseProgram(0);

  //  delete paintbrush;
    delete scenes;
    glfwDestroyWindow(window);
    glfwTerminate();
}
