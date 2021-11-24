/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "AboutScene.h"

#include <GLFW/glfw3.h>

AboutScene::AboutScene() {
    heading = new Font("../fonts/CaveatBrush-Regular.ttf", 100);
    text = new Font("../fonts/arial.ttf", 48);

    int x1 = getWidth() / 2.f, y1 = 200,
        x2 = getWidth() / 2.f + 100, y2 = y1 - 150;
    Rect rect = {
        x1, y1,
        x1, y2,
        y2, y2,
        y2, x1
    };

    NavButton* nav = new NavButton("Main menu", menu, rect, yellow, navType);
    navigation.push_back(nav);
}

/**
 *  Deconstructor.
 */
AboutScene::~AboutScene() {
    // Delete navigation buttons
    while (!navigation.empty()) {
        auto it = navigation.begin();
        delete (*it);
        navigation.erase(it);
    }
}

/**
 *  Draw the about scene on screen.
 */
void AboutScene::draw() {
    // Render title
    heading->RenderText("About", getWidth() / 2.f, getHeight() - 100.f, 1.f,
                        glm::vec3(findColor(yellow).r, findColor(yellow).g, findColor(yellow).b));

    // Render about text
    text->RenderText("You have 30 seconds to draw the word that shows up on the screen.\n"
                     "For each drawing the game guesses what are, you will get a point.",
                      getWidth() / 2.f, getHeight() / 2.f, 1.f, glm::vec3(0.f, 0.f, 0.f));

    // Draw buttons
    for (auto it = navigation.begin(); it != navigation.end(); ++it)
        (*it)->draw();
}
