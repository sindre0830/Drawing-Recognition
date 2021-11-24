/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-23
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
        nav = new NavButton(headings[i], rect, yellow, navType);
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
