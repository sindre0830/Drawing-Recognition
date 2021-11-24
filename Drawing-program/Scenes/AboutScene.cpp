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
    text = new Font("../fonts/CaveatBrush-Regular.ttf", 100);

    int x1 = getWidth() / 2.f, y1 = getHeight() / 2.f - 300,
        x2 = getWidth() / 2.f + 100, y2 = y1 - 150;
    Rect rect = {
        x1, y1,
        x1, y2,
        y2, y2,
        y2, x1
    };

    NavButton* nav = new NavButton("Main menu", rect, yellow, navType);
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
    text->RenderText("About", getWidth() / 2.f, getHeight() - 100.f, 1.f,
                     glm::vec3(findColor(yellow).r, findColor(yellow).g, findColor(yellow).b));

    // Draw buttons
    for (auto it = navigation.begin(); it != navigation.end(); ++it)
        (*it)->draw();
}
