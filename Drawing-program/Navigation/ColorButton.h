#ifndef __COLORBUTTON_H
#define __COLORBUTTON_H

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

#endif 
