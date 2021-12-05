/**
 * @file ColorButton.h
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_COLORBUTTON_H_
#define CLASS_HEADER_COLORBUTTON_H_

/* local libraries */
#include "./button.h"

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

#endif  // CLASS_HEADER_COLORBUTTON_H_
