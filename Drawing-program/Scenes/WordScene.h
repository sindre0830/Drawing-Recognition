/**
 * @file WordScene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef SCENES_WORDSCENE_H_
#define SCENES_WORDSCENE_H_

#include "Scene.h"
#include "../Text/Font.h"

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
