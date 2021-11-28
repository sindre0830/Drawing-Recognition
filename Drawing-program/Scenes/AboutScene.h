/**
 * @file Scene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef SCENES_ABOUTSCENE_H_
#define SCENES_ABOUTSCENE_H_

#include <vector>
#include "Scene.h"
#include "../Text/Font.h"
#include "../Navigation/NavButton.h"

/**
 * Class for rendering the About scene.
 */
class AboutScene : public Scene {
 private:
     Font* heading;
     Font* text;
 public:
     AboutScene();
     ~AboutScene();

     void draw(GLFWwindow* window);
};

#endif  // SCENES_ABOUTSCENE_H_
