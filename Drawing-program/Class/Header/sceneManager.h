/**
 * @file Scene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_SCENEMANAGER_H_
#define CLASS_HEADER_SCENEMANAGER_H_

/* external libraries */
#include <vector>
#include <string>
/* local libraries */
#include "./scene.h"
#include "./menuScene.h"
#include "./aboutScene.h"
#include "./gameScene.h"
#include "./endScene.h"

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
     int points;
 public:
     bool gameStarted;

     SceneManager();
     ~SceneManager();

     void draw(GLFWwindow* window, std::string guessedWord, int timer);
     SceneType getCurrentScene() { return currentScene; }
};

#endif  // CLASS_HEADER_SCENEMANAGER_H_
