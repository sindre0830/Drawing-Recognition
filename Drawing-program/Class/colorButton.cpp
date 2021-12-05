/**
 * @file ColorButton.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/colorButton.h"

/** 
 *	Constructor.
 *	
 *	@param rect - The area of the button
 *	@param color - The color of the button
 *	@see Button::Button
 */
ColorButton::ColorButton(Rect rect, Color color): Button(rect, color) {
    colorValue = colors.find(color)->second;
}
