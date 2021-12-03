/**
 * @file SceneManager.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"

#include "../build/global.h"

SceneManager::SceneManager() {
    // Create all scenes
    menuScene = new MenuScene();
    aboutScene = new AboutScene();
    gameScene = new GameScene();
    currentScene = menu;
}

SceneManager::~SceneManager() {
    // Delete all scenes
    delete menuScene;
    delete aboutScene;
    delete gameScene;
}

/**
 *  Draw the current scene.
 */
void SceneManager::draw(GLFWwindow* window) {
    // Draw the current scene and check if one of them is clicked
    switch (currentScene) {
    case menu: menuScene->draw(window); break;
    case about: aboutScene->draw(window); break;
    case game: gameScene->draw(window); break;
    }

    // Check if the scene is going to be changed
    SceneType next = none;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        switch (currentScene) {
        case menu: next = menuScene->checkButtonClick(x, y); break;
        case about: next = aboutScene->checkButtonClick(x, y); break;
        }

        if (next != none && next != currentScene) currentScene = next;
    }
}
