/**
 * @file EndScene.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_ENDSCENE_H_
#define CLASS_HEADER_ENDSCENE_H_

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

#endif  // CLASS_HEADER_ENDSCENE_H_
