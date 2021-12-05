/**
 * @file EndScene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef SCENES_ENDSCENE_H_
#define SCENES_ENDSCENE_H_

/* local libraries */
#include "./scene.h"
#include "./font.h"

/**
 * Class for rendering the end scene.
 */
class EndScene : public Scene {
 private:
     Font* heading;
 public:
     EndScene();
     ~EndScene();

     void draw(int points);
};

#endif  // SCENES_ENDSCENE_H_
