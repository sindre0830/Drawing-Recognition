/**
 * @file GameScene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_GAMESCENE_H_
#define CLASS_HEADER_GAMESCENE_H_

/* external libraries */
#include <vector>
#include <string>
/* local libraries */
#include "./scene.h"
#include "./paintbrush.h"
#include "./colorButton.h"

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

#endif  // CLASS_HEADER_GAMESCENE_H_
