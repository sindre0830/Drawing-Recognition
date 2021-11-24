/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-24
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "MenuScene.h"

#include <GLFW/glfw3.h>

#include <string>

MenuScene::MenuScene() {
    text = new Font("../fonts/CaveatBrush-Regular.ttf", 100);

    // Create navigation buttons
    std::vector<std::string> headings{ "Exit", "High scores", "About", "Start game" };
    std::vector<SceneType> types{ about, about, about, about };

    int x1 = getWidth() / 2.f, y1 = getHeight() / 2.f - 300,
        x2 = getWidth() / 2.f + 100, y2 = y1 - 150;
    Rect rect = {
        x1, y1,
        x1, y2,
        y2, y2,
        y2, x1
    };

    NavButton* nav = nullptr;
    for (int i = 0; i < headings.size(); i++) {
        nav = new NavButton(headings[i], types[i], rect, yellow, navType);
        navigation.push_back(nav);
        rect.y1 += 150;
        rect.y2 += 150;
    }
}

/**
 *  Deconstructor.
 */
MenuScene::~MenuScene() {
    // Delete navigation buttons
    while (!navigation.empty()) {
        auto it = navigation.begin();
        delete (*it);
        navigation.erase(it);
    }
}

/**
 *  Draw the menu on screen.
 */
void MenuScene::draw() {
    // Render title
    text->RenderText("Drawing Recognition", getWidth() / 2.f, getHeight() - 100.f, 1.f,
                     glm::vec3(findColor(yellow).r, findColor(yellow).g, findColor(yellow).b));

    // Draw buttons
    for (auto it = navigation.begin(); it != navigation.end(); ++it)
        (*it)->draw();
}

/**
 *  Check if one of the navigation butttons are clicked.
 * 
 *  @param x - The x coordinate of the mouse
 *  @param y - The y coordinate of the mouse
 */
SceneType MenuScene::checkButtonClick(double x, double y) {
    for (auto it = navigation.begin(); it != navigation.end(); ++it) {
        if ((*it)->detectClick(x, y))
            return (*it)->getScene();
    }

    return menu;
}
