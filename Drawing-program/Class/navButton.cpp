/**
 * @file NavButton.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/navButton.h"
/* external libraries */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** 
 *	Constructor.
 *	
 *	@param rect - The area of the button
 *	@param color - The color of the button
 *	@see Button::Button
 */
NavButton::NavButton(std::string text, SceneType scene, Rect rect, Color color):
                     Button(rect, color) {
    this->text = text;
    this->scene = scene;
    textRender = new Font("../External/Fonts/arial.ttf", 24);
}

/**
 *  Deconstructor.
 */
NavButton::~NavButton() {
    delete textRender;
}

/**
 *  Draw the button with text on screen.
 */
void NavButton::draw() {
    Button::draw();
    // Set the start point of the text at the lower left corner of the rectangle
    textRender->RenderText(text, getRect().x1 + 10.f, getRect().y2 + 15.f,
                           1.f, glm::vec3(0.f, 0.f, 0.f));
}
