/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_SCENEMANAGER_H_
#define SCENES_SCENEMANAGER_H_

#include "Scene.h"
#include "MenuScene.h"
#include "AboutScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include <vector>
#include <string>

/**
 * Base class for all scenes.
 */
class SceneManager {
 private:
     MenuScene* menuScene;
     AboutScene* aboutScene;
     GameScene* gameScene;
     EndScene* endScene;
     SceneType currentScene;
 public:
     SceneManager();
     ~SceneManager();

     void draw(GLFWwindow* window, std::string guessedWord);
     SceneType getCurrentScene() { return currentScene; }
};

#endif  // SCENES_SCENEMANAGER_H_
