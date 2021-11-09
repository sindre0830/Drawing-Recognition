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
    ColorButton(Rect rect, Color color, ButtonType type);
    ~ColorButton();

    RGB getRGB() { return colorValue; }
};

#endif  // NAVIGATION_COLORBUTTON_H_
