/**
 * @file NavButton.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "NavButton.h"
#include <iostream>
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
NavButton::NavButton(std::string text, SceneType scene, Rect rect, Color color, ButtonType type):
                     Button(rect, color, type) {
    this->text = text;
    this->scene = scene;
    textRender = new Font("../fonts/arial.ttf", 48);
}

/**
 *  Deconstructor.
 */
NavButton::~NavButton() {
}

/**
 *  Draw the button with text on screen.
 */
void NavButton::draw() {
    Button::draw();
    // Set the start point of the text at the lower left corner of the rectangle
    textRender->RenderText(text, getRect().x1, getRect().y1, 1.f, glm::vec3(0.f, 0.f, 0.f));
}
