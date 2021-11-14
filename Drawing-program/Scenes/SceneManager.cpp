/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-14
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}

/**
 *  Draw the current scene.
 */
void SceneManager::draw() {
    currentScene->draw();
}
