/**
 * @file GameScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include <vector>
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
 public:
     GameScene();
     ~GameScene();

     void draw(GLFWwindow* window);
};

#endif  // SCENES_GAMESCENE_H_
