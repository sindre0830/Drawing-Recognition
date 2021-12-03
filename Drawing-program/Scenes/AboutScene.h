/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_ABOUTSCENE_H_
#define SCENES_ABOUTSCENE_H_

#include "Scene.h"
#include "../Text/Font.h"

/**
 * Class for rendering the About scene.
 */
class AboutScene : public Scene {
 private:
     Font* heading;
 public:
     AboutScene();
     ~AboutScene();

     void draw();
};

#endif  // SCENES_ABOUTSCENE_H_
