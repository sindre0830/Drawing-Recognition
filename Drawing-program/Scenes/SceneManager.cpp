/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"
#include "MenuScene.h"
#include "AboutScene.h"

SceneManager::SceneManager() {
    MenuScene* menu = new MenuScene();
    scenes.push_back(menu);

    AboutScene* about = new AboutScene();
    scenes.push_back(about);

    currentScene = menu;
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
void SceneManager::draw() {
    currentScene->draw();
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
