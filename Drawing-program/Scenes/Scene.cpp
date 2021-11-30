/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "Scene.h"
#include "../const.h"

/**
 *  Constructor.
 */
Scene::Scene() {
    width = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
}

/** 
 *  Deconstructor.
 */
Scene::~Scene() {
    while (!navigation.empty()) {
        auto it = navigation.begin();
        delete (*it);
        navigation.erase(it);
    }
}

/**
 *  Draw the screen.
 */
void Scene::draw(GLFWwindow* window) {
    // Draw buttons
    for (auto it = navigation.begin(); it != navigation.end(); ++it)
        (*it)->draw();
}

/**
 *  Check if one of the navigation butttons are clicked.
 *
 *  @param x - The x coordinate of the mouse
 *  @param y - The y coordinate of the mouse
 */
SceneType Scene::checkButtonClick(double x, double y) {
    for (auto it = navigation.begin(); it != navigation.end(); ++it) {
        if ((*it)->detectClick(x, y)) {
            return (*it)->getScene();
        }
    }

    return none;
}

