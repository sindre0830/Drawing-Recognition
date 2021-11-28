/**
 * @file WordScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_WORDSCENE_H_
#define SCENES_WORDSCENE_H_

#include <GLFW/glfw3.h>
#include <vector>
#include "Scene.h"
#include "../Text/Font.h"
#include "../Navigation/NavButton.h"

/**
 * Class for rendering the About scene.
 */
class WordScene : public Scene {
 private:
     Font* text;
 public:
     WordScene();
     ~WordScene();

     void draw(GLFWwindow* window);
};

#endif  // SCENES_WORDSCENE_H_
