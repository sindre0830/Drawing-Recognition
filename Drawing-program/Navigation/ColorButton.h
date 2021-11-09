#ifndef PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_NAVIGATION_COLORBUTTON_H_
#define PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_NAVIGATION_COLORBUTTON_H_

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

#endif  // PROJECTS_DRAWING_RECOGNITION_DRAWING_PROGRAM_NAVIGATION_COLORBUTTON_H_
