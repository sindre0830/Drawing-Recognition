/**
 * @file GameScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_GAMESCENE_H
#define SCENES_GAMESCENE_H

#include <vector>
#include <string>
#include "Scene.h"
#include "../Text/Font.h"
#include "../Paintbrush/Paintbrush.h"
#include "../Navigation/ColorButton.h"

/**
 * Base class for all scenes.
 */
class GameScene : public Scene {
 private:
     Font* text;
     Paintbrush* paintbrush;
     std::vector<ColorButton*> colors;
     std::vector<std::string> words;
     std::string currentWord;
     int timer,
         t;
 public:
     GameScene();
     ~GameScene();

     void draw(GLFWwindow* window);
};

#endif  // SCENES_GAMESCENE_H
