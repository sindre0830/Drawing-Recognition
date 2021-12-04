/**
 * @file GameScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
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
     int points;
     bool allUsed;
 public:
     GameScene();
     ~GameScene();

     void draw(GLFWwindow* window, std::string guessedWord, int timer);
     void randomWord();
     void endRound();
     int getPoints() { return points; }
     bool getAllUsed() { return allUsed; }
};

#endif  // SCENES_GAMESCENE_H_
