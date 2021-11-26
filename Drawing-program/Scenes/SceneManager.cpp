/**
 * @file SceneManager.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"

#include "MenuScene.h"
#include "AboutScene.h"
#include "WordScene.h"
#include "GameScene.h"

SceneManager::SceneManager() {
    MenuScene* menu = new MenuScene();
    scenes.push_back(menu);

    AboutScene* about = new AboutScene();
    scenes.push_back(about);

    WordScene* word = new WordScene();
    scenes.push_back(word);

    GameScene* game = new GameScene();
    scenes.push_back(game);

    currentScene = game;
}

SceneManager::~SceneManager() {
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
    currentScene->draw(window);
}

/**
 *  Check if a button is clicked in the current scene.
 *
 *  @param x - The x coordinate of the mouse
 *  @param y - The y coordinate of the mouse
 */
void SceneManager::changeScene(double x, double y) {
    SceneType scene;
    // This function needs to return a sceneType
    scene = currentScene->checkButtonClick(x, y);

    // Switch to set current scene based on sceneType
    switch (scene) {
    case menu: setScene(scenes[0]); break;
    case about: setScene(scenes[1]); break;
    }
}
