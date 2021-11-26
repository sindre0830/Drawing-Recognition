/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-14
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "Scene.h"

/**
 *  Constructor.
 */
Scene::Scene() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
}

/** 
 *  Deconstructor.
 */
Scene::~Scene() {
}

/**
 *  Draw the screen.
 */
void Scene::draw(GLFWwindow* window) {
}
