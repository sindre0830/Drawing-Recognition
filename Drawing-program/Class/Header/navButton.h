/**
 * @file NavButton.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef NAVIGATION_NAVBUTTON_H_
#define NAVIGATION_NAVBUTTON_H_

/* external libraries */
#include <string>
/* local libraries */
#include "./button.h"
#include "./font.h"
#include "../../Header/functionality.h"

/**
 *	Class for creating and interacting with buttons.
 */
class NavButton : public Button {
 private:
     Font* textRender;
     std::string text;
     SceneType scene;
 public:
     NavButton(std::string text, SceneType scene, Rect rect, Color color);
    ~NavButton();

    void draw();
    SceneType getScene() { return scene; }
};

#endif  // NAVIGATION_NAVBUTTON_H_
