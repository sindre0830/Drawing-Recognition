/**
 * @file ColorButton.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef NAVIGATION_COLORBUTTON_H_
#define NAVIGATION_COLORBUTTON_H_

#include "Button.h"

/**
 *	Class for creating and interacting with buttons.
 */
class ColorButton : public Button {
 private:
    RGB colorValue;
 public:
    ColorButton(Rect rect, Color color);
    ~ColorButton() {}

    RGB getRGB() { return colorValue; }
};

#endif  // NAVIGATION_COLORBUTTON_H_
