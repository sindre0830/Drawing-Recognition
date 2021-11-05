#include "ColorButton.h"

ColorButton::ColorButton(Rect rect, Color color, ButtonType type) : Button(rect, color, type) {
	colorValue = findColor(color);
}


