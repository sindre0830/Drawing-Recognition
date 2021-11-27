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

    float x1 = getWidth() / 2.f - 150.f, y1 = getHeight() / 2.f - 400.f,
          x2 = x1 + 250.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y1,
        x1, y2,
        x2, y2,
        x2, y1
    };

    NavButton* nav = nullptr;
    for (int i = 0; i < headings.size(); i++) {
        nav = new NavButton(headings[i], types[i], rect, yellow, navType);
        navigation.push_back(nav);

        // Change height coordinates so the buttons are spread out
        y2 += 200.f;
        y1 += 200.f;
        rect = {
            x1, y1,
            x1, y2,
            x2, y2,
            x2, y1
        };
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
void MenuScene::draw(GLFWwindow* window) {
    // Render title
    text->RenderText("Drawing Recognition", getWidth() / 2.f - 350.f, getHeight() - 150.f, 1.f,
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
