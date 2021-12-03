/**
 * @file main.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
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

    /*glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);*/

    GLFWwindow* window = glfwCreateWindow(800, 900, "Drawing Recognition", NULL, NULL);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    std::cout << "\nWidth: " << width << " - Height: " << height;

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

    double x, y;  // Mouse position

    float t = 0.f;  // Total time elapsed since start of program


    while (!glfwWindowShouldClose(window)) {
        // Time management
        float dt = glfwGetTime() - t;
        t += dt;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        /*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            // Get mouse position
            glfwGetCursorPos(window, &x, &y);

            // Create point on mouse position
            //paintbrush->createPoint(x, y);
            //scenes->changeScene(x, y);
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            paintbrush->setNewPos(true);
        }*/


        //paintbrush->draw();
        scenes->draw(window);
        //scenes->changeScene(x, y);

        glfwSwapBuffers(window);

        /*/ Change of colors, by pressing keys
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) paintbrush->setNewColor(black);
        else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) paintbrush->setNewColor(red);
        else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) paintbrush->setNewColor(green);
        else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) paintbrush->setNewColor(blue);
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;*/

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
