/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
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
     Font* text;
     std::vector<NavButton*> navigation;
 public:
     AboutScene();
     ~AboutScene();

     void draw();
};

#endif  // SCENES_ABOUTSCENE_H_
