/**
 * @file NavButton.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef NAVIGATION_NAVBUTTON_H_
#define NAVIGATION_NAVBUTTON_H_

#include <string>
#include "Button.h"
#include "../Text/Font.h"
#include "../functions.h"

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
