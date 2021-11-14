/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-14
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_SCENEMANAGER_H_
#define SCENES_SCENEMANAGER_H_

#include "Scene.h"

#include <vector>
#include <iostream>
/**
 * Base class for all scenes.
 */
class SceneManager {
 private:
     Scene* currentScene;
     std::vector<Scene*> scenes;
 public:
     SceneManager();
     ~SceneManager();

     void setScene(int newScene) { currentScene = scenes[newScene]; }
     void draw();
};

#endif  // SCENES_SCENEMANAGER_H_
