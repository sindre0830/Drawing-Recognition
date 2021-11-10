/**
 * @file ColorButton.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "ColorButton.h"

/** 
 *	Constructor.
 *	
 *	@param rect - The area of the button
 *	@param color - The color of the button
 *	@param type - The button type
 *	@see Button::Button
 */
ColorButton::ColorButton(Rect rect, Color color, ButtonType type): Button(rect, color, type) {
    colorValue = findColor(color);
}
