/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_MENUSCENE_H_
#define SCENES_MENUSCENE_H_

#include <vector>
#include "Scene.h"
#include "../Text/Font.h"
#include "../Navigation/NavButton.h"

/**
 * Base class for all scenes.
 */
class MenuScene : public Scene {
 private:
     Font* text;
     std::vector<NavButton*> navigation;
 public:
     MenuScene();
     ~MenuScene();

     void draw();
     SceneType checkButtonClick(double x, double y);
};

#endif  // SCENES_MENUSCENE_H_
