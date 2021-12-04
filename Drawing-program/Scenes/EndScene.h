/**
 * @file EndScene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_ENDSCENE_H_
#define SCENES_ENDSCENE_H_

#include "Scene.h"
#include "../Text/Font.h"

/**
 * Class for rendering the end scene.
 */
class EndScene : public Scene {
 private:
     Font* heading;
     int points;
 public:
     EndScene();
     ~EndScene();

     void draw(int points);
};

#endif  // SCENES_ENDSCENE_H_
