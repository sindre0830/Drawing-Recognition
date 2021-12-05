/**
 * @file Scene.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/scene.h"
/* local libraries */
#include "../Header/functionality.h"

/**
 *  Constructor.
 */
Scene::Scene() {
    text = new Font("../External/Fonts/Roboto-Regular.ttf", 24);
    width = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
}

/** 
 *  Deconstructor.
 */
Scene::~Scene() {
    delete text;
    while (!navigation.empty()) {
        auto it = navigation.begin();
        delete (*it);
        navigation.erase(it);
    }
}

/**
 *  Draw the screen.
 */
void Scene::draw() {
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

