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

    currentScene = about;
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
