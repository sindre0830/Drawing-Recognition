/**
 * @file NavButton.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef NAVIGATION_NAVBUTTON_H_
#define NAVIGATION_NAVBUTTON_H_

#include <string>
#include "Button.h"
#include "../Text/Font.h"
#include "../Scenes/SceneManager.h"

/**
 *	Class for creating and interacting with buttons.
 */
class NavButton : public Button {
 private:
     Font* textRender;
     std::string text;
 public:
     NavButton(std::string text, Rect rect, Color color, ButtonType type);
    ~NavButton();

    void draw();
};

#endif  // NAVIGATION_NAVBUTTON_H_
