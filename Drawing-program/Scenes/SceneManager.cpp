/**
 * @file SceneManager.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"
#include "MenuScene.h"
#include "AboutScene.h"
#include "WordScene.h"
#include "GameScene.h"

SceneManager::SceneManager() {
    // Create all scenes
    MenuScene* menu = new MenuScene();
    scenes.push_back(menu);

    AboutScene* about = new AboutScene();
    scenes.push_back(about);

    WordScene* word = new WordScene();
    scenes.push_back(word);

    GameScene* game = new GameScene();
    scenes.push_back(game);

    currentScene = menu;
}

SceneManager::~SceneManager() {
    // Delete all scenes
    while (!scenes.empty()) {
        auto it = scenes.begin();
        delete (*it);
        scenes.erase(it);
    }
}

/**
 *  Draw the current scene.
 */
void SceneManager::draw(GLFWwindow* window) {
    // Change scene if one of the navigation buttons in the current scene are pressed
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        SceneType scene = currentScene->checkButtonClick(x, y);

        switch (scene) {
        case menu: currentScene = scenes[0]; break;
        case about: currentScene = scenes[1]; break;
        case word: currentScene = scenes[2]; break;
        case game: currentScene = scenes[3]; break;
        }
    }

    currentScene->draw(window);
}
