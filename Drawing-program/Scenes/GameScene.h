/**
 * @file GameScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include <vector>
#include <string>
#include "Scene.h"
#include "../Paintbrush/Paintbrush.h"
#include "../Navigation/ColorButton.h"

/**
 * Base class for all scenes.
 */
class GameScene : public Scene {
 private:
     Paintbrush* paintbrush;
     std::vector<ColorButton*> colors;
     std::vector<std::string> words;
     std::vector<std::string> usedWords;
     std::string currentWord;
     int wordsUsed;
     int t,
         timer;
 public:
     GameScene();
     ~GameScene();

     void draw(GLFWwindow* window);
     void randomWord();
};

#endif  // SCENES_GAMESCENE_H_
