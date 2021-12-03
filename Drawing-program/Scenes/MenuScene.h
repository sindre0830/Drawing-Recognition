/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_MENUSCENE_H_
#define SCENES_MENUSCENE_H_

#include "Scene.h"
#include "../Text/Font.h"

/**
 * Base class for all scenes.
 */
class MenuScene : public Scene {
 private:
     Font* heading;
 public:
     MenuScene();
     ~MenuScene();

     void draw();
};

#endif  // SCENES_MENUSCENE_H_
