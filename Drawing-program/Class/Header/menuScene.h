/**
 * @file Scene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_MENUSCENE_H_
#define CLASS_HEADER_MENUSCENE_H_

/* local libraries */
#include "./scene.h"
#include "./font.h"

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

#endif  // CLASS_HEADER_MENUSCENE_H_
