/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "MenuScene.h"
#include <string>
#include <vector>
#include "../Navigation/NavButton.h"

MenuScene::MenuScene() {
    text = new Font("../fonts/CaveatBrush-Regular.ttf", 100);

    // Create navigation buttons
    std::vector<std::string> headings{ "Start game", "About", "High scores", "Exit" };
    std::vector<SceneType> types{ word, about, about, about };

    int width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    int height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    float x1 = width / 2.f - 150.f, y1 = height / 2.f + 200.f,
          x2 = x1 + 270.f, y2 = y1 + 65.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };

    NavButton* nav = nullptr;
    for (int i = 0; i < headings.size(); i++) {
        nav = new NavButton(headings[i], types[i], rect, yellow);
        addButton(nav);

        // Change height coordinates so the buttons are spread out
        y2 -= 200.f;
        y1 -= 200.f;
        rect = {
            x1, y2,
            x1, y1,
            x2, y1,
            x2, y2
        };
    }
}

/**
 *  Deconstructor.
 */
MenuScene::~MenuScene() {
    delete text;
}

/**
 *  Draw the menu on screen.
 */
void MenuScene::draw(GLFWwindow* window) {
    Scene::draw(window);
    // Render title
    text->RenderText("Drawing Recognition", getWidth() / 2.f - 350.f, getHeight() - 150.f, 1.f,
                     glm::vec3(findColor(yellow).r, findColor(yellow).g, findColor(yellow).b));
}

