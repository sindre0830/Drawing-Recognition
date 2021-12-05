/**
 * @file Scene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_SCENE_H_
#define CLASS_HEADER_SCENE_H_

/* external libraries */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
/* local libraries */
#include "./navButton.h"
#include "../../Header/functionality.h"
#include "./font.h"

/**
 * Base class for all scenes.
 */
class Scene {
 private:
     int width, height;
 protected:
     Font* text;
     std::vector<NavButton*> navigation;
 public:
     Scene();
     ~Scene();

     int getWidth() { return width; }
     int getHeight() { return height; }

     void draw();
     SceneType checkButtonClick(double x, double y);
};

#endif  // CLASS_HEADER_SCENE_H_
