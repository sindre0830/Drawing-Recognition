/**
 * @file GameScene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef SCENES_GAMESCENE_H
#define SCENES_GAMESCENE_H

#include <vector>
#include "Scene.h"
#include "../Text/Font.h"
#include "../Navigation/ColorButton.h"

/**
 * Base class for all scenes.
 */
class GameScene : public Scene {
 private:
     Font* text;
     std::vector<ColorButton*> colors;
 public:
     GameScene();
     ~GameScene();

     void draw();
};

#endif  // SCENES_GAMESCENE_H
