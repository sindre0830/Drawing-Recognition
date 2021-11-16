/**
 * @file NavButton.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef NAVIGATION_NAVBUTTON_H_
#define NAVIGATION_NAVBUTTON_H_

#include "Button.h"
#include "../Text/Font.h"

/**
 *	Class for creating and interacting with buttons.
 */
class NavButton : public Button {
 private:
     Font* text;
 public:
     NavButton(Rect rect, Color color, ButtonType type);
    ~NavButton();

    void draw();
};

#endif  // NAVIGATION_NAVBUTTON_H_
