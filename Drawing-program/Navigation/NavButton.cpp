/**
 * @file NavButton.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "NavButton.h"
#include "../const.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** 
 *	Constructor.
 *	
 *	@param rect - The area of the button
 *	@param color - The color of the button
 *	@param type - The button type
 *	@see Button::Button
 */
NavButton::NavButton(Rect rect, Color color, ButtonType type): Button(rect, color, type) {
    text = new Font("../fonts/arial.ttf", 48);
}

/**
 *  Deconstructor.
 */
NavButton::~NavButton() {
    delete text;
}

/**
 *  Draw the button with text on screen.
 */
void NavButton::draw() {
    Button::draw();
    // Set the star point of the text at the lower left corner of the rectangle
    text->RenderText("Start game", getRect().x1, getRect().y1, 1.f, glm::vec3(0.f, 0.f, 0.f));
}