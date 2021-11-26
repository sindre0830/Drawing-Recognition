/**
 * @file WordScene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "WordScene.h"

#include <GLFW/glfw3.h>
#include <string>

WordScene::WordScene() {
    text = new Font("../fonts/arial.ttf", 48);

    std::vector<std::string> headings{ "Main menu", "Start"  };
    std::vector<SceneType> types{ menu, menu };

    int x1 = getWidth() / 2.f, y1 = 200,
        x2 = getWidth() / 2.f + 100, y2 = y1 - 150;
    Rect rect = {
        x1, y1,
        x1, y2,
        y2, y2,
        y2, x1
    };

    // Create all navigation buttons in the scene
    NavButton* nav = new NavButton("Main menu", menu, rect, yellow, navType);
    navigation.push_back(nav);
    rect.y1 += 150;
    rect.y2 += 150;
    nav = new NavButton("Start", menu, rect, yellow, navType);
    navigation.push_back(nav);
}

/**
 *  Deconstructor.
 */
WordScene::~WordScene() {
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
void WordScene::draw() {
    text->RenderText("Your new word is:", getWidth() / 2.f, getHeight() / 2.f,
                      1.f, glm::vec3(0, 0, 0));
    text->RenderText("BANANA", getWidth() / 2.f, getHeight() / 2.f - 100, 2.f, glm::vec3(0, 0, 0));

    // Draw buttons
    for (auto it = navigation.begin(); it != navigation.end(); ++it)
        (*it)->draw();
}
